#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Activities{
char Name[100];
char StartTime[10];
int Duration;
int priority; 
};


struct Activities * ReadActivities(char* FileName,int *count){
	FILE* ptr = fopen(FileName, "r");
	int ind=0;
    	if (ptr == NULL) {
    	    return 0 ;
   	 }
   	// Reading File Name ,Start Time ,Duration and Priority 
   	char buf[100];
	fscanf(ptr, "%s",buf);
	int size=atoi(buf);
	*count=size;
	struct Activities * AllActivities=malloc(sizeof(struct Activities)*size);	
    	while (fscanf(ptr, "%s",buf)== 1){		
		strcpy(AllActivities[ind].Name,buf);
		fscanf(ptr, "%s",buf);
		strcpy(AllActivities[ind].StartTime,buf);
		fscanf(ptr, "%s",buf);
		AllActivities[ind].Duration=atoi(buf);
		fscanf(ptr, "%s",buf);
		AllActivities[ind].priority=atoi(buf);
       	 	ind++;
	}
return AllActivities;
}

void printActivities(struct Activities *AllActivities,int count){
for (int i=0;i<count;i++){
	printf("\nActivity Name : %s\n",AllActivities[i].Name);
	printf("Start Time : %s\n",AllActivities[i].StartTime);
	printf("Duration : %d\n",AllActivities[i].Duration);
	printf("Priority :  %d\n",AllActivities[i].priority);
}
}

// Sort Activities on the basis of Priority
void SortActivities(struct Activities *AllActivities,int count){
	for (int i=0;i<count;i++){
		for (int j=0;j<count-i-1;j++){
			if (AllActivities[j].priority>AllActivities[j+1].priority){
					struct Activities temp=AllActivities[j];
					AllActivities[j]=AllActivities[j+1];
					AllActivities[j+1]=temp;
			}
		}
	}

}
// Breaking time into Minutes and Hours  
void BreakTime(char *array,int* Hours,int *Minutes){
	if (array[1]==':'){
		*Hours=array[0]-'0';
		*Minutes=(array[2]-'0')*10+(array[3]-'0');
	}
	else{
		*Hours=(array[0]-'0')*10+(array[1]-'0');
		*Minutes=(array[3]-'0')*10+(array[4]-'0');
	}

}


struct DaySchedule{
	//Total minutes in a day are 60*24=1440 and 1 for null character
	char Minutes[1441]; 
};
void Initialize (struct DaySchedule* d ){
	for (int i=0;i<1440;i++){
		d->Minutes[i]='-';
	}
	d->Minutes[1440]='\0';
}
// for each activity taking its details to place in days sechedule 
// as activities are already sorted on the basis of priority so it would be easy to satisfy the priority scheduling 

void PlaceActivity(struct DaySchedule* d,char key ,int startMinutes,int duration){
int found=1;
	duration+=15;//ADDING THE DELAY BETWEEN The Events 

	for (int i=startMinutes;i<startMinutes+duration;i++){
		if (d->Minutes[i]!='-'){// Showing that there is already a task planned in this time slot 
			found=0;
			break;
		}
	}

	if (found){
		for (int i=startMinutes;i<startMinutes+duration;i++){
			d->Minutes[i]=key;
		}
		for (int i=startMinutes+duration;i<startMinutes+duration+15;i++){
			d->Minutes[i]='*';
		}
	}
	else{
		// Need to check the time slots to the left and right of the specified time 
			
		int BackwardStart=-1;
		int currentempty=0;
		for (int i=startMinutes;i>=0;i--){
			if (d->Minutes[i]!='-'){
				currentempty=0;
			}
			else{
				currentempty++;
			}
			if (currentempty==duration){
				BackwardStart=i;
				break;
			}
			
		}
			
		int ForwardStart=1440;
		currentempty=0;
		for (int i=startMinutes+duration;i<1440;i++){
			if (d->Minutes[i]!='-'){
				currentempty=0;
			}
			else{
				currentempty++;
			}
			if (currentempty==duration){
				ForwardStart=i-duration;
				break;
			}
		}	
		if (BackwardStart==-1 && ForwardStart==1440){
						printf("Cannot Sechedule the Activity  %c today ",key);
						return;
				}
		int newStart=0;
		if (startMinutes-BackwardStart>ForwardStart-startMinutes)
			{
				newStart=ForwardStart;
			}
		else{
				newStart=BackwardStart;
			
			}
			
			for (int i=newStart;i<newStart+duration;i++){
				d->Minutes[i]=key;
			}
				for (int i=newStart+duration;i<newStart+duration+15;i++){
						d->Minutes[i]='*';
				}
	}
}

int PlaceActivity2(struct DaySchedule* d,char key ,int startMinutes,int duration){// getting the location where i can play the activity in given schedule 

int found=1;
	for (int i=startMinutes;i<startMinutes+duration;i++){
		if (d->Minutes[i]!='-'){// Showing that there is already a task planned in this time slot 
			found=0;
			break;
		}
	}

	if (found){
		return 0;
	}
	else{
		// Need to check the time slots to the left and right of the specified time 
			
		int BackwardStart=-1;
		int currentempty=0;
		for (int i=startMinutes;i>=0;i--){
			if (d->Minutes[i]!='-'){
				currentempty=0;
			}
			else{
				currentempty++;
			}
			if (currentempty==duration){
				BackwardStart=i;
				break;
			}
			
		}
			
		int ForwardStart=1440;
		currentempty=0;
		for (int i=startMinutes+duration;i<1440;i++){
			if (d->Minutes[i]!='-'){
				currentempty=0;
			}
			else{
				currentempty++;
			}
			if (currentempty==duration){
				ForwardStart=i-duration;
				break;
			}
		}	
		if (BackwardStart==-1 && ForwardStart==1440){
						printf("Cannot Sechedule the Activity  %c today ",key);
						return -1;
				}
		int newStart=0;
		if (startMinutes-BackwardStart>ForwardStart-startMinutes)
			{
				newStart=ForwardStart;
				return newStart;
			}
		else{
				newStart=BackwardStart;
				return newStart;
			}
			
	}

}

void printDetails(struct Activities * AllActivities,int count,char  identifier){
	for (int i=0;i<count;i++){
		if (AllActivities[i].Name[0]==identifier){
			printf("Duration : %d\n",AllActivities[i].Duration);
			break;
		}
	}
}

int main(){
int count=0;
struct Activities * AllActivities=ReadActivities("data.txt",&count);
printf("Activities after Sorting with Priority are as Below : \n");
SortActivities(AllActivities,count);
printActivities(AllActivities,count);
printf("Enter the Number of Days  to Scehdule Activities on : ");
int number;
scanf("%d",&number);
if (number==1){
	struct DaySchedule day;
	Initialize(&day);
	
	for (int i=0;i<count;i++){
		int m,h;
		BreakTime(AllActivities[i].StartTime,&h,&m);
		PlaceActivity(&day,AllActivities[i].Name[0],(h*60)+m,AllActivities[i].Duration);
		
	}
	printf("Schedule Chart(showing in Minutes) is as Below\n");
	for (int i=0;i<1440;i++){
			if (day.Minutes[i]=='*'){
				day.Minutes[i]='-';
			}
			printf("%c",day.Minutes[i]);

		}
		printf("\nStart Times are as Below\n");
	char start='-';
	for (int i=0;i<1440;i++){
			if (day.Minutes[i]!=start && day.Minutes[i]!='-'){
				if (start!='-' || start!='*'){
					
					printf("Activity %c\n",day.Minutes[i]);
					if (i%60<10){
					printf("Starting Time(Minutes) %d:0%d \n", i/60,i%60);
					}
					else{
					printf("Starting Time(Minutes) %d:%d \n", i/60,i%60);
					}
					printDetails(AllActivities,count,day.Minutes[i]);
	
				}
				start=day.Minutes[i];		
		}
	}
}

else if (number>=2){

	struct DaySchedule day[number];
	for (int i=0;i<number;i++){	
		Initialize(&day[i]);
	}
	
	for (int i=0;i<count;i++){
		int m,h;
		BreakTime(AllActivities[i].StartTime,&h,&m);
		int best=100000;
		int bestchart=0;
		for (int j=0;j<number;j++){	
			int loc=PlaceActivity2(&day[j],AllActivities[i].Name[0],(h*60)+m,AllActivities[i].Duration);
			if ( loc!=-1 && loc<best ){
				best=loc;
				bestchart=j;
			}
			
		}	
			
		printf("Best %d\n",best);
		PlaceActivity(&day[bestchart],AllActivities[i].Name[0],(h*60)+m,AllActivities[i].Duration);
		
	}
	for(int j=0;j<number;j++){
		printf("\n                                                               ****************  Day %d **************\n",j+1);
		
			for (int i=0;i<1440;i++){
			if (day[j].Minutes[i]=='*'){
				day[j].Minutes[i]='-';
			}
			printf("%c",day[j].Minutes[i]);
		}
		printf("\nStart Times are as Below\n");
			char start='-';
			for (int k=0;k<1440;k++){
				if (day[j].Minutes[k]!=start && day[j].Minutes[k]!='-'){
				if (start!='-' || start!='*'){			
					printf("Activity %c\n",day[j].Minutes[k]);
					if (k%60<10){
					printf("Starting Time(Minutes) %d:0%d \n", k/60,k%60);
					}
					else{
					printf("Starting Time(Minutes) %d:%d \n", k/60,k%60);
					}
					printDetails(AllActivities,count,day[j].Minutes[k]);
	
				}
///////////////
					start=day[j].Minutes[k];		
				}
			}
		
		}
	
	
	
	



}


return 0;
}
