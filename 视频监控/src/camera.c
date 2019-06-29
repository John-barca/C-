#include <stdio.h>   	//printf scanf
#include <fcntl.h>		//open write read lseek close  	 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>
#include <string.h>

#include "../include/camera.h"
#include "../include/api_v4l2.h"
#include "../include/jpeglib.h"

#define MAX 1024

static unsigned char g_color_buf[FB_SIZE]={0};

int ts_x, ts_y;
int flag = 1;

int  lcd_fd;
int *mmap_fd;
struct jpg_data video_buf;//定义结构体变量

//初始化LCD
int lcd_open(void)
{
	lcd_fd = open("/dev/fb0", O_RDWR);
	
	if(lcd_fd<0)
	{
			printf("open lcd error\n");
			return -1;
	}
	return 0;
}

int mmap_lcd(void)
{
	mmap_fd  = (int *)mmap(	NULL, 					//映射区的开始地址，设置为NULL时表示由系统决定映射区的起始地址
									FB_SIZE, 				//映射区的长度
									PROT_READ|PROT_WRITE, 	//内容可以被读取和写入
									MAP_SHARED,				//共享内存
									lcd_fd, 				//有效的文件描述词
									0						//被映射对象内容的起点
	);
	return lcd_fd;

}

//LCD画点
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color)
{
	*(mmap_fd+y*800+x)=color;
}

//显示摄像头捕捉
int show_video_data(unsigned int x,unsigned int y,char *pjpg_buf,unsigned int jpg_buf_size)  
{
	/*定义解码对象，错误处理对象*/
	struct 	jpeg_decompress_struct 	cinfo;
	struct 	jpeg_error_mgr 			jerr;	
	
	unsigned char 	*pcolor_buf = g_color_buf;
	char 	*pjpg;
	
	unsigned int 	i=0;
	unsigned int	color =0;
	//unsigned int	count =0;
	
	unsigned int 	x_s = x;
	unsigned int 	x_e ;	
	unsigned int 	y_e ;
	
	pjpg = pjpg_buf;

	/*注册出错处理*/
	cinfo.err = jpeg_std_error(&jerr);

	/*创建解码*/
	jpeg_create_decompress(&cinfo);

	/*直接解码内存数据*/		
	jpeg_mem_src(&cinfo,pjpg,jpg_buf_size);
	
	/*读文件头*/
	jpeg_read_header(&cinfo, TRUE);

	/*开始解码*/
	jpeg_start_decompress(&cinfo);	
	
	x_e	= x_s+cinfo.output_width;
	y_e	= y  +cinfo.output_height;	

	/*读解码数据*/
	while(cinfo.output_scanline < cinfo.output_height )
	{		
		pcolor_buf = g_color_buf;
			
		/* 读取jpg一行的rgb值 */
		jpeg_read_scanlines(&cinfo,&pcolor_buf,1);
		
		for(i=0; i<cinfo.output_width; i++)
		{
			/* 获取rgb值 */
			color = 		*(pcolor_buf+2);
			color = color | *(pcolor_buf+1)<<8;
			color = color | *(pcolor_buf)<<16;
			
			/* 显示像素点 */
			lcd_draw_point(x,y,color);
			
			pcolor_buf +=3;
			
			x++;
		}
		
		/* 换行 */
		y++;			
		
		x = x_s;
		
	}		
			
	/*解码完成*/
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

//获取文件个数
int get_file_count(char *root)
{
	DIR *dir;
	struct dirent * ptr;
	int total = 0;
	char path[MAX];
	dir = opendir(root); /* 打开目录*/
	if(dir == NULL)
	{
		perror("fail to open dir");
		exit(1);
	}

	errno = 0;
	while((ptr = readdir(dir)) != NULL)
	{
	//顺序读取每一个目录项；
	//跳过“..”和“.”两个目录
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}
	//printf("%s%s/n",root,ptr->d_name);
	//如果是目录，则递归调用 get_file_count函数

		if(ptr->d_type == DT_DIR)
		{
			sprintf(path,"%s%s/",root,ptr->d_name);
			//printf("%s/n",path);
			total += get_file_count(path);
		}

		if(ptr->d_type == DT_REG)
		{
			total++;
			//printf("%s%s/n",root,ptr->d_name);
		}
	}
	if(errno != 0)
	{
		printf("fail to read dir"); //失败则输出提示信息
		exit(1);
	}
	closedir(dir);
	return total;
}



//显示正常jpg图片
int lcd_draw_jpg(unsigned int x,unsigned int y,const char *pjpg_path)  
{
	/*定义解码对象，错误处理对象*/
	struct 	jpeg_decompress_struct 	cinfo;
	struct 	jpeg_error_mgr 			jerr;	
	
	unsigned char 	*pcolor_buf = g_color_buf;
	char 	*pjpg;
	
	unsigned int 	i=0;
	unsigned int	color =0;
	//unsigned int	count =0;
	
	unsigned int 	x_s = x;
	unsigned int 	x_e ;	
	unsigned int 	y_e ;
	unsigned int	y_n	= y;
	unsigned int	x_n	= x;
	
			 int	jpg_fd;
	unsigned int 	jpg_size;

	if(pjpg_path!=NULL)
	{
		/* 申请jpg资源，权限可读可写 */	
		jpg_fd=open(pjpg_path,O_RDWR);
		
		if(jpg_fd == -1)
		{
		   printf("open %s error\n",pjpg_path);
		   
		   return -1;	
		}	
		
		/* 获取jpg文件的大小 */
		jpg_size=file_size_get(pjpg_path);	
		if(jpg_size<3000)
			return -1;
		
		/* 为jpg文件申请内存空间 */	
		pjpg = malloc(jpg_size);

		/* 读取jpg文件所有内容到内存 */		
		read(jpg_fd,pjpg,jpg_size);
	}
	else
		return -1;

	/*注册出错处理*/
	cinfo.err = jpeg_std_error(&jerr);

	/*创建解码*/
	jpeg_create_decompress(&cinfo);

	/*直接解码内存数据*/		
	jpeg_mem_src(&cinfo,pjpg,jpg_size);
	
	/*读文件头*/
	jpeg_read_header(&cinfo, TRUE);

	/*开始解码*/
	jpeg_start_decompress(&cinfo);	
	
	
	x_e	= x_s +cinfo.output_width;
	y_e	= y  +cinfo.output_height;	

	/*读解码数据*/
	while(cinfo.output_scanline < cinfo.output_height )
	{		
		pcolor_buf = g_color_buf;
		
		/* 读取jpg一行的rgb值 */
		jpeg_read_scanlines(&cinfo,&pcolor_buf,1);
		
		for(i=0; i<cinfo.output_width; i++)
		{	
			/* 获取rgb值 */
			color = 		*(pcolor_buf+2);
			color = color | *(pcolor_buf+1)<<8;
			color = color | *(pcolor_buf)<<16;	
			
			/* 显示像素点 */
			lcd_draw_point(x_n,y_n,color);
			
			pcolor_buf +=3;
			
			x_n++;
		}
		
		/* 换行 */
		y_n++;			
		
		x_n = x_s;		
	}		
			
	/*解码完成*/
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	if(pjpg_path!=NULL)
	{
		/* 关闭jpg文件 */
		close(jpg_fd);	
		
		/* 释放jpg文件内存空间 */
		free(pjpg);		
	}

	return 0;
}

//LCD关闭
void lcd_close(void)
{
	
	/* 取消内存映射 */
	munmap(mmap_fd, FB_SIZE);
	
	/* 关闭LCD设备 */
	close(lcd_fd);
}

//获取jpg文件的大小
unsigned long file_size_get(const char *pfile_path)
{
	unsigned long filesize = -1;	
	struct stat statbuff;
	
	if(stat(pfile_path, &statbuff) < 0)
	{
		return filesize;
	}
	else
	{
		filesize = statbuff.st_size;
	}
	
	return filesize;
}

void *start_routine(void *arg)
{
	while(flag)
	{
		read_ts(&ts_x, &ts_y);
		//printf("==(x,y):(%d, %d)\n", ts_x, ts_y);
	}	
}


void show_jpeg(char *pathname)
{
	int g_lcd_fd = open("/dev/fb0",O_RDWR);

	if(g_lcd_fd == -1)
	{
		printf("open lcd failure\n");
		
	}
	//映射
	int *g_fd_men = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,g_lcd_fd,0);
	if(g_fd_men == NULL)
	{
		printf("mmap g_fd_men failed!\n");
		
	}
	

	//一、为JPEG对象分配空间并初始化
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	//二、指定解压缩数据源

	FILE * infile;
	if ((infile = fopen(pathname, "rb")) == NULL)
	{
		printf("fopen jpg failed!\n");
		
	}
	jpeg_stdio_src(&cinfo, infile);

	//三、获取文件信息
	jpeg_read_header(&cinfo, TRUE);

	//四、解压
	jpeg_start_decompress(&cinfo);

	//五、取出数据
	int x,i;
	char *buffer;
	int row_stride = cinfo.output_width * cinfo.output_components;
	//开辟一行数据空间
	buffer = malloc(row_stride);

	JSAMPROW a;
	printf("a=%c\n", a);
	 
	//六、逐行扫描
	while (cinfo.output_scanline < cinfo.output_height)
    {

		(void) jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buffer, 1); // 读取一行数据
		{
			for(i=0,x=0;x<cinfo.output_width;x++)
			{
				*(g_fd_men+(cinfo.output_scanline-1)*800+x) = buffer[i]<<16|buffer[i+1]<<8|buffer[i+2];
				i=i+3;
			}
		}
		 
    }
	//七、解压完毕
	jpeg_finish_decompress(&cinfo);
	//八、释放资源
	jpeg_destroy_decompress(&cinfo);
    fclose(infile);
	
	munmap(g_fd_men,800*480*4);
	close(g_lcd_fd);

}

int my_camera(void)
{
	
	lcd_open();//打开LCD屏幕	
	mmap_lcd();//创建映射关系，将DDR3中存储的摄像头采集的数据映射到LCD屏幕上显示。
	
	pthread_t ts_thread;
	pthread_create(&ts_thread, NULL, start_routine, NULL);
	
	linux_v4l2_yuyv_init("/dev/video7");//初始化摄像头
	linux_v4l2_start_yuyv_capturing();//开启摄像头捕捉
	
	int cnt=0;
	
	int flag=1;
	
	char path[100];
	
	char z_path[1];
	
	int zp_flag=0;
	while(1)
	{
		if(ts_x>640 && ts_x<800 && ts_y>18 && ts_y<80)//实时监控
		{
			linux_v4l2_get_yuyv_data(&video_buf);//获取摄像头捕捉的画面	
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);//显示摄像头捕捉的画面
		}
		//录像
		if(ts_x>640 && ts_x<800 && ts_y>114 && ts_y<179 && cnt<100){
			
			//cnt=0;
			
			//printf("录像");
			linux_v4l2_get_yuyv_data(&video_buf);
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);
			
			zp_flag=1;
			
			sprintf(path, "image/video/%d.jpg", cnt);
			
			if(flag){
				cnt++;
			}else{
				cnt=0;
			}
			
			if(cnt==99){
				flag=0;
			}
			
			int fd_jpg = open(path, O_RDWR|O_CREAT|O_TRUNC);
			write(fd_jpg, video_buf.jpg_data, video_buf.jpg_size);
			close(fd_jpg);
			
		}
		
		//回放
		if(ts_x>640 && ts_x<800 && ts_y>207 && ts_y<275){
			
			//printf("回放/n");
			int count=get_file_count("image/video/");
			//printf("数量%d/n",count);
			char h_path[count];
			
			int i;
			
			for(i=0;i<count-2;i++){
				sprintf(h_path, "image/video/%d.jpg", i);
				show_jpeg(h_path);
				usleep(6*1000);
			}
			
			i=0;
			if(i==cnt){
				printf("播放完毕，重新播放中/n");
			}
			
		}
		
		//抓拍
		if(zp_flag && ts_x>640 && ts_x<800 && ts_y>303 && ts_y<362){
						
			printf("z p/n");
			
			linux_v4l2_get_yuyv_data(&video_buf);
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);
			
			sprintf(z_path, "image/zp/%d.jpg",0);
			
			int fd_jpg = open(z_path, O_RDWR|O_CREAT|O_TRUNC);
			write(fd_jpg, video_buf.jpg_data, video_buf.jpg_size);
			close(fd_jpg);
			
			show_jpeg(z_path);
			
			zp_flag=0;
		}
		
		if(ts_x>640 && ts_x<800 && ts_y>399 && ts_y<460)//退出监控
		{
			printf("\n======退出监控======\n");
			flag = 0;
			break;
		}
		
		/*
		if(?<x<? && ?<y<?) 录像
		{
			linux_v4l2_get_yuyv_data(&video_buf);//获取摄像头捕捉的画面
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);//显示摄像头捕捉的画面
			
			cnt++;
			sprintf(path, "image/video/%d.jpg", cnt);
			
			fd_jpg = open(path, O_RDWR|O_CREAT|O_TRUNC);
			if(fd_jpg == -1)
			{
				printf("creat err\n");
				printf("video err\n");
			}
			write(fd_jpg, video_buf.jpg_data, video_buf.jpg_size);
			colse(fd_jpg);
			
		}
		
		if(?<x<? && ?<y<?)  播放录制的图像
		{
			利用图片播放视频，图片的数量就是cnt
			
		}
			
		
		*/
		
		
	}
	
	//关闭摄像头
	linux_v4l2_yuyv_quit();
	lcd_close();
	return 0;
}
