//链表中删除la节点
void Delete(node* head, node* la)
{
	node* cur=head;
	node* pre=head;
	while (cur != la && cur)
	{
		pre = cur;
		cur = cur->next;
	}
	if (cur = la)
	{
		pre->next = cur->next;
		free(cur);
		cur = cur->next;
	}
}
