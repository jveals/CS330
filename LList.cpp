/*
 *  LList.cpp
 *  Game
 *
 *  Created by Andrew Peddicord on 2/17/11.
 *  Copyright 2011 Capital University. All rights reserved.
 *
 */

#include "LList.h"
//------------------------------------------------------------
LList::LList() {
	this->size_ = 0;
}

LList::~LList() {
    
}
//------------------------------------------------------------

LList::LList(const LList& source) {
	LListIterator it;
	it.init(source);
	
}

//------------------------------------------------------------
void LList::removeFirst(Drawable *&item) {
	if (this->size_ > 0) {
		item = this->head_->item_;
		if (this->size_ > 1) {
			head_ = this->head_->next_;
		} else {
			delete this->head_;
		}
		size_ --;
	}
}
//------------------------------------------------------------
void LList::append(Drawable *&item){
	ListNode *temp = new ListNode();
	temp->item_ = item;
	
	if (this->size_ == 0) {
		this->head_ = temp;
		this->tail_ = temp;
	} else {
		tail_->next_ = temp;
	}
	size_++;
}
//------------------------------------------------------------
void LList::first(Drawable *&item) const {
	item = head_->item_;
}
//------------------------------------------------------------
void LList::removeDrawable(Drawable *obj) {
	int i;
	Drawable *temp;
	ListNode *prenode;
	ListNode *node = this->head_;
	for (i = 0; i<(this->size_); i++) {
		if (node->item_ == obj) {
			break;
		}
		prenode = node;
		node = node->next_;
	}
	if (i == 0) {
		removeFirst(temp);
		return;
	} else if (i == ((this->size_) - 1)) {
		this->tail_ = prenode;
		prenode->next_ = 0;
	} else {
		prenode->next_ = node->next_;
	}
	delete node;
	size_--;
}
//------------------------------------------------------------
LList& LList::operator=(const LList &list) {
	int i;
	LList *temp = new LList();
	ListNode *node = this->head_;
	for (i = 0; i<(this->size_); i++) {
		temp->append(node->item_);
		node = node->next_;
	}
	return *temp;
}