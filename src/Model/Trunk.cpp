#include "Trunk.h"

using namespace std;

namespace trunk{
	void freeTrunk(vector<Trunk*> v) {
		for (Trunk* t: v) {
			delete t;
		}
	}

	void showTrunks(Trunk* p) {
		if (p == nullptr) {
			return;
		}

		showTrunks(p->prev);
		cout << p->str;
	}
}
