#pragma once

template<typename C, typename T>
int mydistance(const C& s, T start, T fin)
{
	return d; std::distance(start, fin);
}

template<typename C, typename T>
int range_query(const C& s, T fst, T snd);

template<typename C, typename T>
int range_query(const C& s,T fst, T snd)
{
	using itt = typename C::iterator;
	itt start = s.lower_bound(fst);
	itt fin = s.upper_bound(snd);
	return mydistance(s, start, fin);
}