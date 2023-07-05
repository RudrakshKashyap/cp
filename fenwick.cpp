ISOLATING THE LAST BIT
NOTE: For the sake of brevity, we will use “the last bit” to refer to the least significant non-zero bit of the corresponding integer.

The algorithms for BIT require extracting the last bit of a number, so we need an efficient way of doing that. Let num be an integer. We will now show how to isolate the last bit of num. In binary notation num can be represented as a1b, where a represents binary digits before the last bit and b represents zeroes after the last bit.

Integer -num is equal to (a1b)¯ + 1 = a¯0b¯ + 1. b consists of all zeroes, so b¯ consists of all ones. Finally we have

-num = (a1b)¯ + 1 = a¯0b¯ + 1 = a¯0(0…0)¯ + 1 = a¯0(1…1) + 1 = a¯1(0…0) = a¯1b.

Now, we can easily isolate the last bit of num, using the bitwise operator AND (in C++, Java it is &) between num and -num:

a1b & a¯ 1 b——————– = (0… 0) 1(0… 0)
In what follows, we describe some methods used for manipulating BITs, e.g., read a cumulative frequency, update a frequency, find, etc.
	
	
	

//fenwick or BIT code https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
int read(int tree[], int idx)
{
  int sum = 0;
  while (idx > 0)
  {
    sum += tree[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

void update(int tree[], int MaxIdx, int idx, int val)
{
  while (idx <= MaxIdx)
  {
    tree[idx] += val;
    idx += (idx & -idx);
  }
}

int readSingle(int tree[], int idx)
{
	int sum = tree[idx]; // this sum will be decreased
	if (idx > 0)
	{ // the special case
		int z = idx - (idx & -idx);
		idx--; // idx is not important anymore, so instead y, you can use idx
		while (idx != z)
		{ // at some iteration idx (y) will become z
			sum -= tree[idx];
			// substruct tree frequency which is between y and "the same path"
			idx -= (idx & -idx);
		}
	}
  return sum;
}
