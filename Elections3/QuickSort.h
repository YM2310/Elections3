#pragma once
template<typename Iter>
void Swap(Iter _a, Iter _b)
{
	auto temp = *_b;
	*_b = *_a;
	*_a = temp;
}
template <class Iterator>
int distance(Iterator left, Iterator right) {
	Iterator temp = left;
	int diff = 0;
	while (temp != right) {
		temp++;
		diff++;
	}
	return diff;
}

template <class Iterator, class Compare>
void quickSort(Iterator left, Iterator right, const Compare& cmp) {
	if (right - left > 0)
	{
		Iterator pivot = partition(left, right, cmp);
		quickSort(left, pivot - 1, cmp);
		quickSort(pivot + 1, right, cmp);
	}
}
//cmp(a,b) if a> b return true
template <class Iterator, class Compare>
Iterator partition(Iterator left, Iterator right, Compare& cmp)
{
	Iterator pivot = right;
	Iterator end = right;
	Iterator i = left;
	i--;

	for (Iterator j = left; j != end; j++)
	{
		if (cmp(*pivot, *j))
		{
			i++;
			Swap(i, j);
		}
	}
	i++;
	Swap(i, pivot);
	return i;
}

