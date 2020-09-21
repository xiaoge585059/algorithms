
#include <iostream>
using namespace std;

class UnionFind {
private:
	int n;  // 触点数量
	int* id;  // 以触点为索引的数组，来表示所有分量
	int* size;  // 用于加权 quick-union
	int union_count;  // 连通分量的数量
	int choice;

public:
	/* 以整数标识(0 到 n - 1)初始化 n 个触点 */
	UnionFind(int n, int choice) {
		this->n = n;
		this->union_count = n;
		this->id = new int[n];
		this->size = new int[n];
		for (int i = 0; i < n; ++i) {
			this->id[i] = i;
			this->size[i] = 1;
		}

		this->choice = choice;
	}

	~UnionFind() {
		delete[] this->id, this->size;
	}

	/**
	 * 三种 find 和 union 实现方式
	 *   find: p(0 到 n - 1)所在的分量的标识符
	 *   union: 在 p 和 q 之间添加一条连接
	 */

	/* 1.quick-find */

	int quick_find(int p) {
		return this->id[p];
	}

	void create_union_with_quick_find(int p, int q) {
		// 将 p 和 q 归并到相同的分量中
		int p_id = quick_find(p);
		int q_id = quick_find(q);

		// 如果 p 和 q 已经在相同的分量之中则不需要采取任何行动
		if (p_id == q_id) {
			return;
		}

		// 将 p 的分量重命名为 q 的名称
		for (int i = 0; i < this->n; ++i) {
			if (this->id[i] == p_id) {
				this->id[i] = q_id;
			}
		}

		this->union_count -= 1;
	}

	/* 2.quick-union */

	int find_with_quick_union(int p) {
		while (p != this->id[p]) {
			p = this->id[p];
		}
		return p;
	}

	void quick_create_union(int p, int q) {
		// 将 p 和 q 的根节点统一
		int p_root = find_with_quick_union(p);
		int q_root = find_with_quick_union(q);
		if (p_root == q_root) {
			return;
		}
		this->id[p_root] = q_root;

		this->union_count -= 1;
	}

	/* 3.加权 quick-union */

	int find_with_weight(int p) {
		// 跟随链接找到根节点
		while (p != this->id[p]) {
			p = this->id[p];
		}
		return p;
	}

	void quick_create_union_with_weight(int p, int q) {
		int i = find_with_weight(p);
		int j = find_with_weight(q);
		if (i == j) {
			return;
		}

		// 将小树的根节点连接到大树的根节点
		if (this->size[i] < this->size[j]) {
			this->id[i] = j;
			this->size[j] += this->size[i];
		} else {
			this->id[j] = i;
			this->size[i] += this->size[j];
		}

		this->union_count -= 1;
	}

	/* 3.(改进版)压缩路径的加权 quick-union */
	int compress_path_find_with_weight(int p) {
		int p_root = p;
		while (p_root != this->id[p_root]) {
			p_root = this->id[p_root];
		}
		// p 节点到 p 所在的连通分量的根节点所形成的路径上，所有节点都直接指向根节点
		while (p != p_root) {
			int temp_id = this->id[p];
			this->id[p] = p_root;
			p = temp_id;
		}

		return p_root;
	}

	int find(int p) {
		if (this->choice == 0) {
			return quick_find(p);
		} else if (this->choice == 1) {
			return find_with_quick_union(p);
		} else if (this->choice == 2) {
			return find_with_weight(p);
		} else if (this->choice == 3) {
			return compress_path_find_with_weight(p);
		}

		return -1;
	}

	void create_union(int p, int q) {
		if (this->choice == 0) {
			create_union_with_quick_find(p, q);
		} else if (this->choice == 1) {
			quick_create_union(p, q);
		} else if (this->choice == 2 || this->choice == 3) {
			quick_create_union_with_weight(p, q);
		}
	}

	/* 如果 p 和 q 存在于同一个分量中则返回 true */
	bool connected(int p, int q) {
		return find(p) == find(q);
	}

	/* 联通分量的数量 */
	int count() {
		return this->union_count;
	}
};

void test_UnionFind() {
	// 4, 3, 3, 8, 6, 5, 9, 4, 2, 1, 5, 0, 7, 2, 6, 1
	int a[22] = { 4, 3, 3, 8, 6, 5, 9, 4, 2, 1, 8, 9, 5, 0, 7, 2, 6, 1, 1, 0, 6, 7 };
	for (int choice = 0; choice < 4; ++choice) {
		UnionFind uf(10, choice);
		for (int i = 0; i < 22; i += 2) {
			int p = a[i];
			int q = a[i + 1];
			if (uf.connected(p, q)) {
				continue;
			}
			uf.create_union(p, q);
			cout << p << " " << q << endl;
		}
		cout << uf.count() << " components" << endl;
		cout << "-------------------------" << endl;
	}
}


/* 测试 */
/*
int main() {
	test_UnionFind();

	return 0;
} //*/
