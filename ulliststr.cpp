#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_) return NULL;
  Item* cur = head_;
  size_t idx = loc;
  while (cur)
  {
    size_t used = cur->last - cur->first;
    if (idx < used) return &cur->val[cur->first + idx];
    idx -= used;
    cur = cur->next;
  }
  return NULL;
}

void ULListStr::push_back(const std::string& val)
{
  if (empty())
  {
    head_ = tail_ = new Item();
    head_->first = head_->last = 0;
  }
  if (tail_->last == ARRSIZE)
  {
    Item* n = new Item();
    n->first = n->last = 0;
    n->prev = tail_;
    tail_->next = n;
    tail_ = n;
  }
  tail_->val[tail_->last++] = val;
  ++size_;
}

void ULListStr::push_front(const std::string& val)
{
  if (empty())
  {
    head_ = tail_ = new Item();
    head_->first = head_->last = ARRSIZE;
  }
  if (head_->first == 0)
  {
    Item* n = new Item();
    n->first = n->last = ARRSIZE;
    n->next = head_;
    head_->prev = n;
    head_ = n;
  }
  head_->val[--head_->first] = val;
  ++size_;
}

void ULListStr::pop_back()
{
  if (empty()) return;
  --tail_->last;
  --size_;
  if (tail_->first == tail_->last)
  {
    Item* dead = tail_;
    tail_ = tail_->prev;
    if (tail_) tail_->next = NULL;
    else head_ = NULL;
    delete dead;
  }
}

void ULListStr::pop_front()
{
  if (empty()) return;
  ++head_->first;
  --size_;
  if (head_->first == head_->last)
  {
    Item* dead = head_;
    head_ = head_->next;
    if (head_) head_->prev = NULL;
    else tail_ = NULL;
    delete dead;
  }
}

std::string const& ULListStr::front() const { return head_->val[head_->first]; }
std::string const& ULListStr::back()  const { return tail_->val[tail_->last - 1]; }

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
