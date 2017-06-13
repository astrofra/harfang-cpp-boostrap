// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

struct container_sort {
	template <typename T, typename L, typename C> static void quicksort(L &t, C compare) { quicksort_step<T, L, C>(t, compare, 0, t.size() - 1); }

private:
	template <typename T, typename L> static inline void swap(L &t, int i, int j) {
		if (i != j) {
			T swap = t[j]; t[j] = t[i]; t[i] = swap;
		}
	}

	template <typename T, typename L, typename C> static int quicksort_partition(L &t, C compare, int first, int last, int pivot) {
		swap<T, L>(t, pivot, last);

		int j = first;
		for (int i = first; i < last; ++i)
			if (compare(t[i], t[last]) > 0) {
				swap<T, L>(t, i, j);
				++j;
			}

		swap<T, L>(t, j, last);
		return j;
	}

	template <typename T, typename L, typename C> static void quicksort_step(L &t, C compare, int first, int last) {
		if (first < last) {
			int pivot = (first + last) / 2;
			pivot = quicksort_partition<T, L, C>(t, compare, first, last, pivot);

			quicksort_step<T, L, C>(t, compare, first, pivot - 1);
			quicksort_step<T, L, C>(t, compare, pivot + 1, last);
		}
	}
};

} // gs
