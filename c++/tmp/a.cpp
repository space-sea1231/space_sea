void Div() {
	memset(c, 0, sizeof(c));
	int l = 1, r = 0, top = 0;
	for (int i = lena; i; i--) {
		c[++r] = a[i];
		while (l < r && !c[l]) l++;
		int L = 0, R = 9, d = 0;
		while (L <= R) {
			int mid = (L + R) >> 1, x = 0;
			int lent = lenb;
			for (int j = 1; j <= lenb; j++) {
				tmp[j] = b[j] * mid + x;
				x = tmp[j] / 10;
				tmp[j] %= 10;
			}
			while (x) {
				tmp[++lent] = x % 10;
				x /= 10;
			}
			while (lent > 1 && !tmp[lent]) lent--;
			int lenc = r - l + 1;
			bool flag = (lent <= lenc);
			if (lent == lenc) {
				for (int k = l; k <= r; k++) {
					if (tmp[r - k + 1] > c[k]) {
						flag = false;
						break;
					} else if (tmp[r - k + 1] < c[k]) break;
				}
			}
			if (flag) {
				d = mid;
				L = mid + 1;
			} else R = mid - 1;
		}
		q[++top] = d;
		if (d) {
			int lent = lenb, x = 0;
			for (int j = 1; j <= lenb; j++) {
				tmp[j] = b[j] * d + x;
				x = tmp[j] / 10;
				tmp[j] %= 10;
			}
			while (x) {
				tmp[++lent] = x % 10;
				x /= 10;
			}
			while (lent > 1 && !tmp[lent]) lent--;
			for (int k = r; k >= l; k--) {
				int idx = r - k + 1;
				if (idx <= lent) c[k] -= tmp[idx];
				if (c[k] < 0) {
					c[k] += 10;
					c[k - 1]--;
				}
			}
		}
	}
	int lpos = 1;
	while (lpos < top && !q[lpos]) lpos++;
	for (int i = lpos; i <= top; i++) printf("%d", q[i]);
	printf("\n");
	while (l < r && !c[l]) l++;
	for (int i = l; i <= r; i++) printf("%lld", c[i]);
	printf("\n");
}