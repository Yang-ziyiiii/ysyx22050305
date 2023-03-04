/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char expr[65536];
  word_t value;
  
  /* TODO: Add more members if necessary */
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
void new_wp(char *expr, word_t value){
  if (free_ == NULL){
	printf("Free is NULL\n");
	assert(0);
  }
  WP *new = NULL;
  new = free_;
  free_ = free_->next;
  new->value = value;
  //new->expr = expr;
  strcpy(new->expr,expr);
  //printf("doing here5\n");
  new->next = NULL;
  if (head == NULL){
    head=new;
  }
  else{
	new->next = head;
	head = new;
  }
  printf("A new watch %d point is added,with value: 0x%016lx\n",new->NO,new->value);
  return;
}

void free_wp (int NO){
  WP *p = head;
  if (head == NULL){
    printf("Head is NULL\n");
    assert(0);
  }
  else if(p->NO == NO) //head is special
  {
    head=head->next;
    p->value = 0;
    p->next = free_;
    free_ = p;
    printf("NO:%d has been deleted\n",NO);
    return;
  }
  else{
    WP *q = head;
    p = p -> next;
    while(p!= NULL){
      if(p->NO == NO){
        q->next = p->next;
        p->value = 0;
        p->next = free_;
        free_ = p;
        printf("NO:%d has been deleted\n",NO);
        return;
      }
      else {
        p = p->next;
        q = q->next;
      }
    }
  }
  printf("delete fault\n");
  return ;
}

void print_wp(){
  WP *p = head;
  if (p == NULL){
    printf("Head is NULL\n");
    return;
  }
  else{
    while(p != NULL){
      printf("No:%d %s 0x%016lx\n",p->NO, p->expr, p->value);
      p = p->next;
    }
    return;
  }
  return;
}

bool check_wp(){
  WP *p = head;
  bool success = true;
  bool change = false;
  word_t value;
  if (p == NULL){
    return change;
  }
  else{
    while(p != NULL){
      value = expr(p->expr,&success); 
      if(value != p->value){
        printf("No:%d %s has changed from 0x%08lx to 0x%08lx now\n",p->NO, p->expr, p->value,value);
	p->value = value;
	change = true;
      }	
      p = p->next;
    }
    return change;
  }
}

