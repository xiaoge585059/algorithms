
#include <iostream>
using namespace std;

class UnionFind {
private:
	int n;  // ��������
	int* id;  // �Դ���Ϊ���������飬����ʾ���з���
	int* size;  // ���ڼ�Ȩ quick-union
	int union_count;  // ��ͨ����������
	int choice;

public:
	/* ��������ʶ(0 �� n - 1)��ʼ�� n ������ */
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
	 * ���� find �� union ʵ�ַ�ʽ
	 *   find: p(0 �� n - 1)���ڵķ����ı�ʶ��
	 *   union: �� p �� q ֮�����һ������
	 */

	/* 1.quick-find */

	int quick_find(int p) {
		return this->id[p];
	}

	void create_union_with_quick_find(int p, int q) {
		// �� p �� q �鲢����ͬ�ķ�����
		int p_id = quick_find(p);
		int q_id = quick_find(q);

		// ��� p �� q �Ѿ�����ͬ�ķ���֮������Ҫ��ȡ�κ��ж�
		if (p_id == q_id) {
			return;
		}

		// �� p �ķ���������Ϊ q ������
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
		// �� p �� q �ĸ��ڵ�ͳһ
		int p_root = find_with_quick_union(p);
		int q_root = find_with_quick_union(q);
		if (p_root == q_root) {
			return;
		}
		this->id[p_root] = q_root;

		this->union_count -= 1;
	}

	/* 3.��Ȩ quick-union */

	int find_with_weight(int p) {
		// ���������ҵ����ڵ�
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

		// ��С���ĸ��ڵ����ӵ������ĸ��ڵ�
		if (this->size[i] < this->size[j]) {
			this->id[i] = j;
			this->size[j] += this->size[i];
		} else {
			this->id[j] = i;
			this->size[i] += this->size[j];
		}

		this->union_count -= 1;
	}

	/* 3.(�Ľ���)ѹ��·���ļ�Ȩ quick-union */
	int compress_path_find_with_weight(int p) {
		int p_root = p;
		while (p_root != this->id[p_root]) {
			p_root = this->id[p_root];
		}
		// p �ڵ㵽 p ���ڵ���ͨ�����ĸ��ڵ����γɵ�·���ϣ����нڵ㶼ֱ��ָ����ڵ�
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

	/* ��� p �� q ������ͬһ���������򷵻� true */
	bool connected(int p, int q) {
		return find(p) == find(q);
	}

	/* ��ͨ���������� */
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


/* ���� */
/*
int main() {
	test_UnionFind();

	return 0;
} //*/
