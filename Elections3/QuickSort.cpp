
template <class Iterator,class Compare>
void quickSort(Iterator left, Iterator right, const Compare& cmp) {
	if (left < right)
	{
		Iterator pivot = partition(left, right,cmp);
		quickSort(left, pivot - 1,cmp);
		quickSort(pivot + 1, right,cmp);
	}
}
//cmp(a,b) if a> b return true
template <class Iterator, class Compare>
Iterator partition(Iterator left, Iterator right, const Compare& cmp)
{
	Iterator tmp;
	Iterator pivot = right;
	Iterator i = left;
	i--;

	for (Iterator j = left; j != right; ++j)
	{
		if (cmp(*j, *pivot))
		{
			i++;
			tmp = *i;
			*i=*j
			*j=*tmp

		}
	}
	tmp = ++i
	*i=*right;
	*right=*tmp;
	return i;
}