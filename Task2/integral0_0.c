#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
  CURL *curl =curl_easy_init();

  if(!curl){
    fprintf(stderr, "curl init failed\n");
    return EXIT_FAILURE;
  }
  //user interactions
  unsigned int n;
  double x;
  scanf("%d",&n);
  scanf("%lf",&x);
  char appID[]="X5T6GG-EU8WLPV74R";
  char url_req[1024];
  char *wolf_inp=calloc(512,sizeof(char));
  char *target = wolf_inp;
    //double *a = calloc(n,sizeof(double));
  target += sprintf(wolf_inp,"integrate%%20");
  double b;
  for ( unsigned int k =n; k>0;--k){
    scanf("%lf",&b);
    target += sprintf(target, "%lf%%2Ax%%5E%d%%2B",b,k); 
  }
  scanf("%lf",&b);
  target += sprintf(target, "%lg%%20",b);
  target += sprintf(target, "dx%%20from%%20x%%3D0%%20to%%20%lf",x);
//  printf("\n%s\n%s\n",wolf_inp,target);
  sprintf(url_req,"http://api.wolframalpha.com/v1/result"
      "?appid=%s&i=%s%%3f", appID,wolf_inp);
//printf("\n\n%s\n\n",url_req);


  //set options
  curl_easy_setopt(curl,CURLOPT_URL,url_req);

//perform out actions
  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK){
    fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));
  }
  printf("\n");
  free(wolf_inp);
  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}
