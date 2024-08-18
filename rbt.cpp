#include <iostream>
#include <ctime>
using namespace std;

enum Colour
{
	RED,
	BLACK,
};
 
//template<class K, class V>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _father;
 
	int _key;
	int _value;
 
	Colour _col;
 
	RBTreeNode(const int& key, const int& value)
		:_left(NULL)
		, _right(NULL)
		, _father(NULL)
		, _key(key)
		, _value(value)
		, _col(RED)
	{}
	RBTreeNode(const int& key, const int&value, RBTreeNode *nilT)
		:_left(nilT)
		, _right(nilT)
		, _father(NULL)
		, _key(key)
		, _value(value)
		, _col(RED)
	{
	}
};
 
RBTreeNode *mroot, *NilT;
int maxb = 1, nnum = 0;
inline void lrotate(RBTreeNode *u)
{
	RBTreeNode *father = u->_father;
	RBTreeNode *gfather = father->_father;
 
	if (gfather != NULL)
	{
		if (father == gfather->_left)
		{
			gfather->_left = u;
		}
		else
		{
			gfather->_right = u;
		}
	}
	else
	{
		mroot = u;
	}
	father->_right = u->_left;
	father->_right->_father = father;
	father->_father = u;
 
	u->_left = father;
	u->_father = gfather;
}
 
inline void rrotate(RBTreeNode *u)
{
	RBTreeNode *father = u->_father;
	RBTreeNode *gfather = father->_father;
 
	if (gfather != NULL)
	{
		if (father == gfather->_left)
		{
			gfather->_left = u;
		}
		else
		{
			gfather->_right = u;
		}
	}
	else
	{
		mroot = u;
	}
	father->_left = u->_right;
	father->_left->_father = father;
	father->_father = u;
 
	u->_right = father;
	u->_father = gfather;
}
 
void RBTreeFix(RBTreeNode *v)
{
	while (true)
	{
		RBTreeNode* u = v->_father;
		RBTreeNode* gu = u->_father;

		if (gu->_left == u && u->_left == v)
		{
			if (gu->_right->_col == BLACK)
			{
				rrotate(u);
				gu->_col = RED;
				u->_col = BLACK;
			}
			else
			{
				gu->_right->_col = BLACK;
				u->_col = BLACK;
				if (gu != mroot)
				{
					gu->_col = RED;
					if (gu->_father->_col == RED)
					{
						//RBTreeFix(gu);
						v = gu;
						continue;
					}
				}
				else
				{
					maxb++;
				}
			}
		}
		else if (gu->_left == u && u->_right == v)
		{
			if (gu->_right->_col == BLACK)
			{
				lrotate(v);
				rrotate(v);
				gu->_col = RED;
				v->_col = BLACK;
			}
			else
			{
				gu->_right->_col = BLACK;
				u->_col = BLACK;
				if (gu != mroot)
				{
					gu->_col = RED;
					if (gu->_father->_col == RED)
					{
						v = gu;
						continue;
					}
				}
				else
				{
					maxb++;
				}
			}
		}
		else if (gu->_right == u && u->_left == v)
		{
			if (gu->_left->_col == BLACK)
			{
				rrotate(v);
				lrotate(v);
				v->_col = BLACK;
				gu->_col = RED;
			}
			else
			{
				gu->_left->_col = BLACK;
				u->_col = BLACK;
				if (gu != mroot)
				{
					gu->_col = RED;
					if (gu->_father->_col == RED)
					{
						v = gu;
						continue;
					}
				}
				else
				{
					maxb++;
				}
			}
		}
		else
		{
			if (gu->_left->_col == BLACK)
			{
				lrotate(u);
				u->_col = BLACK;
				gu->_col = RED;
			}
			else
			{
				gu->_left->_col = BLACK;
				u->_col = BLACK;
				if (gu != mroot)
				{
					gu->_col = RED;
					if (gu->_father->_col == RED)
					{
						v = gu;
						continue;
					}
				}
				else
				{
					maxb++;
				}
			}
		}
		break;
	}
}
 
inline void minsert(RBTreeNode *u, int mkey, int mvalue)
{
	if (u == NilT)
	{
		mroot = new RBTreeNode(mkey, mvalue, NilT);
		mroot->_col = BLACK;
		maxb++;
		nnum++;
		return;
	}
 
	RBTreeNode *v = new RBTreeNode(mkey, mvalue, NilT);
	while (true)
	{
		if (u->_key == mkey)
		{
			u->_value = mvalue;
			return;
		}
		if (mkey < u->_key)
		{
			if (u->_left == NilT)
			{
				nnum++;
				u->_left = v;
				v->_father = u;
				if (u->_col == RED)
				{
					RBTreeFix(v);
				}
				break;
			}
			else
			{
				u = u->_left;
			}
		}
		else
		{
			if (u->_right == NilT)
			{
				nnum++;
				u->_right = v;
				v->_father = u;
				if (u->_col == RED)
					RBTreeFix(v);
				break;
			}
			else
			{
				u = u->_right;
			}
		}
	}
}
 
inline RBTreeNode *mfind(RBTreeNode *u, int mkey)
{
	while(u != NilT)
	{
		if (u->_key == mkey)
		{
			return u;
		}
		else if (u->_key < mkey)
		{
			u = u->_right;
		}
		else
		{
			u = u->_left;
		}
	}
	return NULL;
}
 
inline RBTreeNode *msucc(RBTreeNode *u)
{
	u = u->_right;
	while (u->_left != NilT)
		u = u->_left;
	return u;
}
 
inline RBTreeNode *mprx(RBTreeNode *u)
{
	u = u->_left;
	while (u->_right != NilT)
		u = u->_right;
	return u;
}
 
inline void RBDFix(RBTreeNode *x)
{
	while (x != mroot && x->_col == BLACK)
	{
		RBTreeNode *fax = x->_father;
		if (x == fax->_left)
		{
			RBTreeNode *w = fax->_right;
			if (w->_col == RED)
			{
				w->_col = BLACK;
				fax->_col = RED;
				lrotate(w);
			}
			w = fax->_right;
			if (w->_left->_col == BLACK && w->_right->_col == BLACK)
			{
				w->_col = RED;
				x = fax;
				continue;
			}
			else
			{
				if (w->_right->_col == BLACK)
				{
					w->_col = RED;
					w->_left->_col = BLACK;
					rrotate(w->_left);
				}
				w = fax->_right;
				w->_col = fax->_col;
				fax->_col = BLACK;
				w->_right->_col = BLACK;
				lrotate(w);
				break;
			}
		}
		else
		{
			RBTreeNode *fax = x->_father;
			RBTreeNode *w = fax->_left;
			if (w->_col == RED)
			{
				w->_col = BLACK;
				fax->_col = RED;
				rrotate(w);
			}
			w = fax->_left;
			if (w->_left->_col == BLACK && w->_right->_col == BLACK)
			{
				w->_col = RED;
				x = fax;
				continue;
			}
			else
			{
				if (w->_left->_col == BLACK)
				{
					w->_col = RED;
					w->_right->_col = BLACK;
					lrotate(w->_right);
				}
				w = fax->_left;
				w->_left->_col = BLACK;
				w->_col = fax->_col;
				fax->_col = BLACK;
				rrotate(w);
				break;
			}
		}
	}
	if (x == mroot)
		maxb--;
	else
		x->_col = BLACK;
}
 
inline RBTreeNode* RBTreeDelete(RBTreeNode *u)
{
	nnum--;
	RBTreeNode *y,*x,*fax;
	if (u->_left == NilT || u->_right == NilT)
	{
		y = u;
	}
	else
	{
		y = msucc(u);
	}
	if(y->_left != NilT)
	{
		x = y->_left;
	}
	else
	{
		x = y->_right;
	}
	fax = y->_father;
	x->_father = fax;
	if (fax != NULL)
	{
		if (fax->_left == y)
		{
			fax->_left = x;
		}
		else
		{
			fax->_right = x;
		}
	}
	else
	{
		mroot = x;
	}
	if (y != u)
	{
		u->_value = y->_value;
		u->_key = y->_key;
	}
	if (y->_col == BLACK)
	{
		RBDFix(x);
	}
	
	return y;
}
 
void preorder(RBTreeNode *u, int bstep)
{
	bool flag = false;
	if (u->_col == BLACK)
		bstep++;
	else
		flag = true;
	if (u == NilT)
	{
		if (bstep != maxb)
			cout << "false" << endl;
		return;
	}
	if (flag && u->_left->_col == RED)
		cout << "false" << endl;
	preorder(u->_left, bstep);
	//cout << u->_key << " ";
 
	if (flag && u->_right->_col == RED)
		cout << "false" << endl;
	preorder(u->_right, bstep);
}

int getRand()
{
	int mymod = (1 << 15);
	return ((rand() % mymod) << 15) + (rand() % mymod);
}
int main()
{
	//cout << RAND_MAX << endl;
	srand(time(NULL));
	//RBTreeNode *mroot = new RBTreeNode(0, 0);
	//mroot -> _col = BLACK;
	NilT = new RBTreeNode(0, 0);
	NilT->_col = BLACK;
	mroot = NilT;
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 32767; i++)
		{
			minsert(mroot, getRand(), getRand());
			if (i % 100 == 0)
				preorder(mroot, 0);
		}
		if (mroot->_col != BLACK)
			cout << "false" << endl;
		preorder(mroot, 0);

		cout << maxb << " " << nnum << endl;
		for (int i = 0; i < 32767; i++)
		{
			RBTreeNode* y = mfind(mroot, getRand());
			if (y != NULL)
			{
				y = RBTreeDelete(y);
				delete y;
			}
			if (i % 100 == 0)
				preorder(mroot, 0);
		}
		cout << maxb << " " << nnum << endl;
	}
	//cout << "Yes" << endl;
	//system("pause");
}

