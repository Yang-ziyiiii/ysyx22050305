#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  while(*s){
    s++;
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  if((dst == NULL)||(src == NULL)) return NULL;
  char *ret = dst;
  while((*dst++ = *src++)!='\0');
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  if((dst == NULL)||(src == NULL)) return NULL;
  char *ret = dst;
  int i = 0;
  while((*dst++ = *src++)&&(i++ < n ))
    if(*(--dst)!='\0')
      *dst = '\0';
  return ret;
}


char *strcat(char *dst, const char *src) {
  char *ret = dst;
  while(*dst !='\0'){dst++;}
  while((*dst++ = *src++)!='\0'){;}
  return ret;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 == *s2)
  {	
  	if(*s1 == '\0'){return 0;}
  	s1++;
  	s2++;
  }
  return *s1 - *s2;
}


int strncmp(const char *s1, const char *s2, size_t n) {
  if(!n) return 0;
  while(--n && *s1 && (*s1 == *s2))
  {
  	s1++;
  	s2++;
  }
  return *s1 - *s2;
}

void *memset(void *s, int c, size_t n) {
  if(s == NULL || n<0) return NULL;
  char *str = (char *)s;
  while(n-- > 0){*str++ = c;}
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  if(dst == NULL || src == NULL || n < 0) return NULL;
  void* rest = dst;
  if(dst < src)
  {
    while(n--)
    {
      *(char*)dst = *(char*)src;
      (char*)dst++;
      (char*)src++;
    }
  }
  else
  {
    while(n--)
    {
      *((char*)dst + n) = *((char*)src + n);
    }
  }
  return rest;
}

void *memcpy(void *out, const void *in, size_t n) {
  if(NULL == out || NULL == in || n < 0) return NULL;
  char *tempout = (char *)out;
  char *tempin = (char *)in;
  while(n-- > 0){*tempout++ = *tempin++;}
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char *temps1 = (char*)s1;
  char *temps2 = (char*)s2;
  while(--n && *temps1 == *temps2)
  {
    temps1++;
    temps2++;
  }
  return *temps1 - *temps2;
}

#endif
