# powersof2.c
powersof2.c has this fun predicate:
```c
!(((a&-a)^a)??!??!!(a<<!(a^a)|a>>~(~(a^a)<<!(a^a))))
```

Let's break it down:
First, `??!` is a [trigraph in C](https://en.wikipedia.org/wiki/Digraphs_and_trigraphs#C) for `|`, so we get:
```c
!(((a&-a)^a) || !(a<<!(a^a)|a>>~(~(a^a)<<!(a^a))))
```

Distribute the `!` over the disjunction, swap the resulting conjuncts, and we get a (slightly) more readable version:
```c
 (a<<!(a^a)|a>>~(~(a^a)<<!(a^a))) && !((a&-a)^a)
```

Not much better, but at least we have 2 separate conjuncts. Now we can focus on each part.

First, `(a<<!(a^a)|a>>~(~(a^a)<<!(a^a)))`

`a^a = 0` and `!0` is just 1, so:
```c
a<<1|a>>~(~0<<1)
```

`~0 << 1 = ...1110`, which we then invert to `...0001`. So `~(~0<<1)` is just a ridiculous way of saying `1`:
```c
a<<1|a>>1
```

Since we don't need to worry about values of `a` above 10000 the highest order bit will always be 0, so `a<<1` will never shift off a 1. Any non-zero value is evaluated is a true value, and we will never lose any non-zero bits in `a<<1`, so we can safely convert that to just `a`. `a>>1` can only cause us to lose non-zero bits, therefore `a != 0` => `a>>1 != 0`, so we can simplify `a<<1|a>>1` to just:
```c
a
```

So one of the conjuncts is just "a is non-zero". Let's look at `!((a&-a)^a)` now.

Through the magic of [2's complement](https://en.wikipedia.org/wiki/Two%27s_complement), `(a & -a) ^ a == 0` does the actual check to see if `a` is a power of 2 (or 0, hence the `&& a`). This is more idiomatically expressed as `(a & -a) == a`.

This ridiculousness is best illustrated with examples:

| `a` | `a` (bin)  | `-a` | `a & -a` | `(a & -a) ^ a` | Power of 2?       |
| --- | ---------  | ---- | -------- | -------------- | ----------------- |
| 0   | 0000       | 0000 | 0000     | 0000           | No (special case) |
| 1   | 0001       | 1111 | 0001     | 1110           | No                |
| 2   | 0010       | 1110 | 0010     | 0000           | Yes               |
| 3   | 0011       | 1101 | 0001     | 0010           | No                |
| 4   | 0100       | 1100 | 0100     | 0000           | Yes               |
| 5   | 0101       | 1011 | 0001     | 0100           | No                |
| ... | ...        | ...  | ...      | ...            | ...               |
| 8   | 1000       | 1000 | 1000     | 0000           | Yes               |

After all that, we finally get `a && (a & -a) == a`

So the predicate is true if `a` is a power of 2.
