#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//int main(){
//    int fd = open("/dev/fb0", O_RDWR);
//    int buf[800 * 480];
//    int i = 0;
//    for(i = 0; i < 800 * 480; i++){
//        if(i < 800 * 160){
//            buf[i] = 0xff00;
//        }
//        else if(i < 800 * 320){
//            buf[i] = 0xff;
//        }else{
//            buf[i] = 0xff0000;
//        }
//    }
//    ssize_t n = write(fd, buf, sizeof(buf));
//    close(fd);
//    return 0;
//}
//

//int main(){
//    int led_fd = open("/dev/fb0", O_RDWR);
//    int buf[480][800] = { 0 };
//    int i = 0;
//    for(i = 0; i < 480; i++) {
//        int j = 0;
//        for(j = 0; j < 800; j++){
//            if(j < 800 / 3){
//                buf[i][j] = 0xff0000;
//            }
//            else if((j >= 800 / 3) && (j < (800 * 2 / 3))){
//                buf[i][j] = 0xff00;
//            }else {
//                buf[i][j] = 0xff;
//            }
//        }
//    }  
//    ssize_t n = write(led_fd, buf, sizeof(buf));
//
//    close(led_fd);
//    return 0;
//}
//
int main(){
    int led_fd = open("/dev/fb0", O_RDWR);

    int buf[480][800] = { 0 };
    int row = 0; //行
    for(row = 0; row < 480; row++){
        int col = 0;
        for(col = 0; col < 800; col++){
            int num = 1;// 显示颜色的像素点
            
        }
    }

    return 0;
}