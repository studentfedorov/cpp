#include "../include/clist.h"
#include "../include/position.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void remove_position(struct intrusive_list *l, int x, int y) {
	struct intrusive_node *cur = l -> head, t;
	struct position_node *p;
	bool del = false;
	if (cur == NULL)
		return;
	int sz = get_length(l);
	while (sz--){
		p = container_of(cur, struct position_node, node);
		if (p -> x == x && p -> y == y)
			del = true;
		cur = cur -> next;
		if (del){
			remove_node(l, cur -> prev);
			free(p);
			del = false;
		}
	}
}

void add_position(struct intrusive_list *l, int x, int y) {
	struct position_node *p = malloc(sizeof(*p));
	p -> x = x;
	p -> y = y;
	add_node(l, &(p -> node));
}

void show_all_positions(struct intrusive_list *l) {
	struct intrusive_node *cur = l -> head;
	struct position_node *p;
	if (cur == NULL)
		return;
	do{
		p = container_of(cur, struct position_node, node);
		printf("(%d %d) ", p -> x, p -> y);
		cur = cur -> next;
	}while (cur != l -> head);
}

void remove_all_positions(struct intrusive_list *l) {
	struct position_node *p;
	while (l -> head != NULL){
		p = container_of(l -> head, struct position_node, node);
		remove_node(l, l -> head);
		free(p);
	}
}