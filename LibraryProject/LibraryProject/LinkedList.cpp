//
//  LinkedList.cpp
//  Assignment3
//
//  Created by Chris M on 5/2/16.
//  Copyright © 2016 Chris McPherson. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "LinkedList.h"


using namespace std;

LinkedList::LinkedList()
{
    first_=0;
    last_= 0;
    curNode_ =0;
    listLen_ =0;
}
LinkedList::~LinkedList()
{
    
    if (first_ != 0)
    {
        Node * tempNode;
        curNode_ = first_;
        if (first_->next_){
            tempNode = first_->next_;
        }
        delete first_;
        curNode_ = tempNode;
        while (curNode_ !=0)
        {
            tempNode =curNode_;
            if (first_->next_){
                curNode_ = curNode_->next_;
            }
            tempNode->prev_=NULL;
            delete tempNode;
        }
    }
}

void LinkedList::SetCurNode(Node* current)
{
    curNode_ = current;
}
void LinkedList::AddLinkToBack(void* ptr)
{
    if (first_ == 0 )
    {
        
        Node* lnk = new Node();
        first_ = lnk;
        last_ = lnk;
        curNode_  = first_;
        first_->data_ = ptr;
    }
    else
    {
        Node* lnk = new Node;
        lnk->data_=ptr;
        lnk->prev_ = last_;
        last_->next_ = lnk;
        last_ = lnk;
        last_->next_ =NULL;
        curNode_ = lnk;
        
    }
    listLen_++;
    
}
void* LinkedList::RemoveLinkFromFront()
{
    Node * ptr= 0;
    if (first_!=0)
    {
        ptr = first_;
        first_ = first_->next_;
        listLen_--;
        delete ptr;
    }
    return first_;
}

void* LinkedList::RemoveThisLink(Node* node)
{
    Node * tempDelLnk = node;
    if (node == first_) {
        first_ = first_->next_;
        
        curNode_=first_;
    }else if(node == last_){
        last_ = last_->prev_;
        
    }else{
        Node * tempPrevLnk = tempDelLnk->prev_;
        Node * tempNextLnk = tempDelLnk->next_;
        tempPrevLnk->next_ = tempNextLnk;
        tempNextLnk->prev_ = tempPrevLnk;
    }
    delete tempDelLnk;
    listLen_--;
    return curNode_;
    
}
void* LinkedList::GetFirstNode()
{
    curNode_ =first_;
    return curNode_;
}
void* LinkedList::GetNextNode()
{
    if (curNode_->next_ !=0)
    {
        curNode_= curNode_->next_;
        return curNode_;
    }else
    {
        return curNode_;
    }
}
void* LinkedList::GetCurNode()
{
    return curNode_;
}

long LinkedList::GetListLength()
{
    return listLen_;
}