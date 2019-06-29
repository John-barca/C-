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
struct jpg_data video_buf;//����ṹ�����

//��ʼ��LCD
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
	mmap_fd  = (int *)mmap(	NULL, 					//ӳ�����Ŀ�ʼ��ַ������ΪNULLʱ��ʾ��ϵͳ����ӳ��������ʼ��ַ
									FB_SIZE, 				//ӳ�����ĳ���
									PROT_READ|PROT_WRITE, 	//���ݿ��Ա���ȡ��д��
									MAP_SHARED,				//�����ڴ�
									lcd_fd, 				//��Ч���ļ�������
									0						//��ӳ��������ݵ����
	);
	return lcd_fd;

}

//LCD����
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color)
{
	*(mmap_fd+y*800+x)=color;
}

//��ʾ����ͷ��׽
int show_video_data(unsigned int x,unsigned int y,char *pjpg_buf,unsigned int jpg_buf_size)  
{
	/*���������󣬴��������*/
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

	/*ע�������*/
	cinfo.err = jpeg_std_error(&jerr);

	/*��������*/
	jpeg_create_decompress(&cinfo);

	/*ֱ�ӽ����ڴ�����*/		
	jpeg_mem_src(&cinfo,pjpg,jpg_buf_size);
	
	/*���ļ�ͷ*/
	jpeg_read_header(&cinfo, TRUE);

	/*��ʼ����*/
	jpeg_start_decompress(&cinfo);	
	
	x_e	= x_s+cinfo.output_width;
	y_e	= y  +cinfo.output_height;	

	/*����������*/
	while(cinfo.output_scanline < cinfo.output_height )
	{		
		pcolor_buf = g_color_buf;
			
		/* ��ȡjpgһ�е�rgbֵ */
		jpeg_read_scanlines(&cinfo,&pcolor_buf,1);
		
		for(i=0; i<cinfo.output_width; i++)
		{
			/* ��ȡrgbֵ */
			color = 		*(pcolor_buf+2);
			color = color | *(pcolor_buf+1)<<8;
			color = color | *(pcolor_buf)<<16;
			
			/* ��ʾ���ص� */
			lcd_draw_point(x,y,color);
			
			pcolor_buf +=3;
			
			x++;
		}
		
		/* ���� */
		y++;			
		
		x = x_s;
		
	}		
			
	/*�������*/
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

//��ȡ�ļ�����
int get_file_count(char *root)
{
	DIR *dir;
	struct dirent * ptr;
	int total = 0;
	char path[MAX];
	dir = opendir(root); /* ��Ŀ¼*/
	if(dir == NULL)
	{
		perror("fail to open dir");
		exit(1);
	}

	errno = 0;
	while((ptr = readdir(dir)) != NULL)
	{
	//˳���ȡÿһ��Ŀ¼�
	//������..���͡�.������Ŀ¼
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}
	//printf("%s%s/n",root,ptr->d_name);
	//�����Ŀ¼����ݹ���� get_file_count����

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
		printf("fail to read dir"); //ʧ���������ʾ��Ϣ
		exit(1);
	}
	closedir(dir);
	return total;
}



//��ʾ����jpgͼƬ
int lcd_draw_jpg(unsigned int x,unsigned int y,const char *pjpg_path)  
{
	/*���������󣬴��������*/
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
		/* ����jpg��Դ��Ȩ�޿ɶ���д */	
		jpg_fd=open(pjpg_path,O_RDWR);
		
		if(jpg_fd == -1)
		{
		   printf("open %s error\n",pjpg_path);
		   
		   return -1;	
		}	
		
		/* ��ȡjpg�ļ��Ĵ�С */
		jpg_size=file_size_get(pjpg_path);	
		if(jpg_size<3000)
			return -1;
		
		/* Ϊjpg�ļ������ڴ�ռ� */	
		pjpg = malloc(jpg_size);

		/* ��ȡjpg�ļ��������ݵ��ڴ� */		
		read(jpg_fd,pjpg,jpg_size);
	}
	else
		return -1;

	/*ע�������*/
	cinfo.err = jpeg_std_error(&jerr);

	/*��������*/
	jpeg_create_decompress(&cinfo);

	/*ֱ�ӽ����ڴ�����*/		
	jpeg_mem_src(&cinfo,pjpg,jpg_size);
	
	/*���ļ�ͷ*/
	jpeg_read_header(&cinfo, TRUE);

	/*��ʼ����*/
	jpeg_start_decompress(&cinfo);	
	
	
	x_e	= x_s +cinfo.output_width;
	y_e	= y  +cinfo.output_height;	

	/*����������*/
	while(cinfo.output_scanline < cinfo.output_height )
	{		
		pcolor_buf = g_color_buf;
		
		/* ��ȡjpgһ�е�rgbֵ */
		jpeg_read_scanlines(&cinfo,&pcolor_buf,1);
		
		for(i=0; i<cinfo.output_width; i++)
		{	
			/* ��ȡrgbֵ */
			color = 		*(pcolor_buf+2);
			color = color | *(pcolor_buf+1)<<8;
			color = color | *(pcolor_buf)<<16;	
			
			/* ��ʾ���ص� */
			lcd_draw_point(x_n,y_n,color);
			
			pcolor_buf +=3;
			
			x_n++;
		}
		
		/* ���� */
		y_n++;			
		
		x_n = x_s;		
	}		
			
	/*�������*/
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	if(pjpg_path!=NULL)
	{
		/* �ر�jpg�ļ� */
		close(jpg_fd);	
		
		/* �ͷ�jpg�ļ��ڴ�ռ� */
		free(pjpg);		
	}

	return 0;
}

//LCD�ر�
void lcd_close(void)
{
	
	/* ȡ���ڴ�ӳ�� */
	munmap(mmap_fd, FB_SIZE);
	
	/* �ر�LCD�豸 */
	close(lcd_fd);
}

//��ȡjpg�ļ��Ĵ�С
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
	//ӳ��
	int *g_fd_men = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,g_lcd_fd,0);
	if(g_fd_men == NULL)
	{
		printf("mmap g_fd_men failed!\n");
		
	}
	

	//һ��ΪJPEG�������ռ䲢��ʼ��
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	//����ָ����ѹ������Դ

	FILE * infile;
	if ((infile = fopen(pathname, "rb")) == NULL)
	{
		printf("fopen jpg failed!\n");
		
	}
	jpeg_stdio_src(&cinfo, infile);

	//������ȡ�ļ���Ϣ
	jpeg_read_header(&cinfo, TRUE);

	//�ġ���ѹ
	jpeg_start_decompress(&cinfo);

	//�塢ȡ������
	int x,i;
	char *buffer;
	int row_stride = cinfo.output_width * cinfo.output_components;
	//����һ�����ݿռ�
	buffer = malloc(row_stride);

	JSAMPROW a;
	printf("a=%c\n", a);
	 
	//��������ɨ��
	while (cinfo.output_scanline < cinfo.output_height)
    {

		(void) jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buffer, 1); // ��ȡһ������
		{
			for(i=0,x=0;x<cinfo.output_width;x++)
			{
				*(g_fd_men+(cinfo.output_scanline-1)*800+x) = buffer[i]<<16|buffer[i+1]<<8|buffer[i+2];
				i=i+3;
			}
		}
		 
    }
	//�ߡ���ѹ���
	jpeg_finish_decompress(&cinfo);
	//�ˡ��ͷ���Դ
	jpeg_destroy_decompress(&cinfo);
    fclose(infile);
	
	munmap(g_fd_men,800*480*4);
	close(g_lcd_fd);

}

int my_camera(void)
{
	
	lcd_open();//��LCD��Ļ	
	mmap_lcd();//����ӳ���ϵ����DDR3�д洢������ͷ�ɼ�������ӳ�䵽LCD��Ļ����ʾ��
	
	pthread_t ts_thread;
	pthread_create(&ts_thread, NULL, start_routine, NULL);
	
	linux_v4l2_yuyv_init("/dev/video7");//��ʼ������ͷ
	linux_v4l2_start_yuyv_capturing();//��������ͷ��׽
	
	int cnt=0;
	
	int flag=1;
	
	char path[100];
	
	char z_path[1];
	
	int zp_flag=0;
	while(1)
	{
		if(ts_x>640 && ts_x<800 && ts_y>18 && ts_y<80)//ʵʱ���
		{
			linux_v4l2_get_yuyv_data(&video_buf);//��ȡ����ͷ��׽�Ļ���	
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);//��ʾ����ͷ��׽�Ļ���
		}
		//¼��
		if(ts_x>640 && ts_x<800 && ts_y>114 && ts_y<179 && cnt<100){
			
			//cnt=0;
			
			//printf("¼��");
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
		
		//�ط�
		if(ts_x>640 && ts_x<800 && ts_y>207 && ts_y<275){
			
			//printf("�ط�/n");
			int count=get_file_count("image/video/");
			//printf("����%d/n",count);
			char h_path[count];
			
			int i;
			
			for(i=0;i<count-2;i++){
				sprintf(h_path, "image/video/%d.jpg", i);
				show_jpeg(h_path);
				usleep(6*1000);
			}
			
			i=0;
			if(i==cnt){
				printf("������ϣ����²�����/n");
			}
			
		}
		
		//ץ��
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
		
		if(ts_x>640 && ts_x<800 && ts_y>399 && ts_y<460)//�˳����
		{
			printf("\n======�˳����======\n");
			flag = 0;
			break;
		}
		
		/*
		if(?<x<? && ?<y<?) ¼��
		{
			linux_v4l2_get_yuyv_data(&video_buf);//��ȡ����ͷ��׽�Ļ���
			show_video_data(0, 0, video_buf.jpg_data, video_buf.jpg_size);//��ʾ����ͷ��׽�Ļ���
			
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
		
		if(?<x<? && ?<y<?)  ����¼�Ƶ�ͼ��
		{
			����ͼƬ������Ƶ��ͼƬ����������cnt
			
		}
			
		
		*/
		
		
	}
	
	//�ر�����ͷ
	linux_v4l2_yuyv_quit();
	lcd_close();
	return 0;
}
