/*
*线段树模板
*luogu P3372
*/
#include <iostream>
struct Tree
{
	int l, r;
	long long val, lazy_tag;
} tree[4 * (int)1e5 + 5];
long long arr[(int)1e5 + 5];
void Build(int p, int l, int r)
{
	tree[p].l = l;
	tree[p].r = r;
	if (l == r)
	{
		tree[p].val = arr[l];
		return;
	}
	int mid = (tree[p].l + tree[p].r) >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
	tree[p].val = tree[p << 1].val + tree[p << 1 | 1].val;
}
void PushDown(int p)
{
	if (tree[p].lazy_tag == 0)
		return;
	if (tree[p].l == tree[p].r)
	{
		tree[p].lazy_tag = 0;
		return;
	}
	tree[p << 1].val += (tree[p << 1].r - tree[p << 1].l + 1) * tree[p].lazy_tag;
	tree[p << 1 | 1].val += (tree[p << 1 | 1].r - tree[p << 1 | 1].l + 1) * tree[p].lazy_tag;
	tree[p << 1].lazy_tag += tree[p].lazy_tag;
	tree[p << 1 | 1].lazy_tag += tree[p].lazy_tag;
	tree[p].lazy_tag = 0;
}
void Modify(int p, int l, int r, int v)
{
	if (tree[p].l <= l && r <= tree[p].r)
	{
		tree[p].val += (r - l + 1) * v;
		if (tree[p].l == l && r == tree[p].r)
		{
			tree[p].lazy_tag += v;
			return;
		}
	}
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (r <= mid)
		Modify(p << 1, l, r, v);
	else if (l >= mid + 1)
		Modify(p << 1 | 1, l, r, v);
	else if (l <= mid && r >= mid + 1)
	{
		Modify(p << 1, l, mid, v);
		Modify(p << 1 | 1, mid + 1, r, v);
	}
}
long long Query(int p, int l, int r)
{
	PushDown(p);
	if (l == tree[p].l && tree[p].r == r)
		return tree[p].val;
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (r <= mid)
		return Query(p << 1, l, r);
	else if (l >= mid + 1)
		return Query(p << 1 | 1, l, r);
	else
		return Query(p << 1, l, mid) + Query(p << 1 | 1, mid + 1, r);
}
int main()
{
	int n, m, opt, x, y, k;
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> arr[i];
	Build(1, 1, n);
	while (m--)
	{
		std::cin >> opt >> x >> y;
		switch (opt)
		{
		case 1:
			std::cin >> k;
			Modify(1, x, y, k);
			break;
		case 2:
			std::cout << Query(1, x, y) << std::endl;
			break;
		}
	}
	return 0;
}