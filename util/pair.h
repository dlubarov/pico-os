template <class A, class B>
struct Pair
{
    A first;
    B second;

    Pair(A fst, B snd)
      : first(fst),
        second(snd) {}
};
