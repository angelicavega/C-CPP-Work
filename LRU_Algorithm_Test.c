/* LRU Page Replacement Algorithm */

#include"stdio.h"
 //--------------------------------
int calcLRU(int time[], int n){
    int i, minimum = time[0], pos = 0;
 
    for(i = 1; i < n; ++i){
        if(time[i] < minimum){
            minimum = time[i];
            pos = i;
        }
    }
    
    return pos;
}
 //--------------------------------
int main()
{
 //--------------------------------
    int calc_frames, calc_references, frames[10], references[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &calc_frames);
    
    printf("Enter number of refereces: ");
    scanf("%d", &calc_references);
    
    printf("Enter reference string: ");
    
    for(i = 0; i < calc_references; ++i){
        scanf("%d", &references[i]);
    }
    
    for(i = 0; i < calc_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < calc_references; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < calc_frames; ++j){
            if(frames[j] == references[i]){
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        
        if(flag1 == 0){
            for(j = 0; j < calc_frames; ++j){
                if(frames[j] == -1){
                    counter++;
                    faults++;
                    frames[j] = references[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }   
        }
        
        if(flag2 == 0){
            pos = calcLRU(time, calc_frames);
            counter++;
            faults++;
            frames[pos] = references[i];
            time[pos] = counter;
        }
        
        printf("\n");
        
        for(j = 0; j < calc_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
  //--------------------------------  
    printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}