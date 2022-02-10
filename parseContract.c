#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fsci_file "/var/fsci"
#define PATH_MAX        4096	/* # chars in a path name including nul */



 int _get_cloudvm_seatcount() {
	char buf[PATH_MAX] = { 0 };
	char *p;
	FILE *fp = NULL;
	struct tm tms;
	time_t t;
	int d, s, n, r;

	fp = fopen(fsci_file, "r");
	if (fp) {
		fread(buf, sizeof(buf), 1, fp);
		fclose(fp);

		p = strstr(buf, "FSAW");
		if (p) {
			r = sscanf(p, "FSAW-%d-%d-%d:%d:%d:", &n, &n, &d, &n, &s);
			if (5 == r) {
				time(&t);
				localtime_r(&t, &tms);
				if (((tms.tm_year + 1900) * 10000 + (tms.tm_mon + 1) * 100 + tms.tm_mday) <= d)
					return s;
			}
		}
	}
	return 0;
}

 int checkContract() {
	char buf[PATH_MAX] = { 0 };
	char *p;
	FILE *fp = NULL;
	struct tm tms;
	time_t t;
	int d, s, n, r, contractDay;

	fp = fopen(fsci_file, "r");
	if (fp) {
		fread(buf, sizeof(buf), 1, fp);
		fclose(fp);

		p = strstr(buf, "AVDB");
		if (p) {
			r = sscanf(p, "AVDB-%d-%d-%d:%d:%d:", &n, &n, &d, &n, &s);
			if (5 == r) {
				time(&t);
				localtime_r(&t, &tms);
				contractDay = ((tms.tm_year + 1900) * 10000 + (tms.tm_mon + 1) * 100 + tms.tm_mday);
				if((d - contractDay) > 0 
					&& (d - contractDay) <= 15)
					return d;
			}
		}
	}
	return 0;
}

int checkExpire(char* buf, char* type) {
	struct tm tms_now;
	struct tm* tms_c;
	time_t rawtime, t_now, t_c;
	int d, s, n, r, duration, i;
	char *p;
	// char format[30];
	char *format = (char *) malloc(strlen(type) + strlen("-%d-%d-%d:%d:%d:"));
        sprintf(format, "%s%s", type, "-%d-%d-%d:%d:%d:");
	const int day[6]={1, 2, 3, 7, 15, 30};

	p = strstr(buf, type);
	if (p) {
		// strcpy(format, type);
    	//strcat(type,"-%d-%d-%d:%d:%d:");
		r = sscanf(p, format,  &n, &n, &d, &n, &s);
		if (5 == r) {
		    time ( &rawtime );
    		tms_c = localtime ( &rawtime );

			tms_c->tm_year = d / 10000 -1900;
			tms_c->tm_mon = (d / 100) % 100 - 1;
			tms_c->tm_mday = d % 100;
			
			t_c = mktime(tms_c);

			time(&t_now);
			localtime_r(&t_now, &tms_now);

			duration = (int) (difftime(t_c, t_now)/(3600*24));
			for (i = 0; i < 6; i++) {
				if (day[i] == duration)
				{
					return duration;
				}
			}
			// if(duration >= 0 
			// 	&& duration <= 15)
			// 	return duration;
		}
		if (format !=NULL){
			free(format);
			format = NULL;
		}
	}
	return -1;
}

int checkExpire2(char buf[], char type[]) {
	struct tm tms_now;
	struct tm tms_c;
	time_t rawtime, t_now, t_c;
	int d, s, n, r, duration, i;
	char *p;
	const int day[6]={1, 2, 3, 7, 15, 30};
    char *format = (char *) malloc(strlen(type) + strlen("-%d-%d-%d:%d:%d:") + 1);
    sprintf(format, "%s%s", type, "-%d-%d-%d:%d:%d:");

	p = strstr(buf, type);
	if (p) {
		r = sscanf(p, format,  &n, &n, &d, &n, &s);
		if (5 == r) {
		    time( &t_now );
			localtime_r( &t_now, &tms_c );

			tms_c.tm_year = d / 10000 -1900;
			tms_c.tm_mon = (d / 100) % 100 - 1;
			tms_c.tm_mday = d % 100;
			t_c = mktime(&tms_c);

			//time(&t_now);
			//localtime_r(&t_now, &tms_now);

			duration = (int) (difftime(t_c, t_now)/(3600*24));
			for (i = 0; i < 6; i++) {
				if (day[i] == duration)
				{
					break;
				}
			}
		}
	}
	free(format);
	format = NULL;

	if (duration > 0) {
		return duration;
	} else {
		return -1;
	}

}

 int checkContract2() {
	//char buf[PATH_MAX] = { 0 };
	char *p;
	FILE *fp = NULL;
	char *buf = NULL;
	int len;
	int fileLen;
    size_t ret_code;

		// buf = (char *) malloc(5000);
	fp = fopen(fsci_file, "r");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		fileLen = ftell(fp);
		buf = (char *) malloc(sizeof(char) * fileLen + 1);
		fseek(fp, 0, SEEK_SET);
		ret_code = fread(buf, fileLen, 1, fp);
		fclose(fp);

        buf[fileLen] = '\0';

		len =checkExpire2(buf, "AVDB"); 

               if (buf != NULL) {
                       free(buf);
                       buf = NULL;
               }
		return len;
	}
	return 0;
}


int main()
{
	//printf("%d\n",_get_cloudvm_seatcount());
	printf("%d\n",checkContract2());
	return (0);
	
}