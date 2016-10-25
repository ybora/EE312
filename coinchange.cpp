

Martian change(value) {
    if value == 0:
        return empty martian;
    if value < 0:
        you messed up;
    m1 = change(value - 12);
    m2 = change(value - 5);
    m3 = change(value - 1);
}

Martian change2(value, Martian m0) {
    if (value < 0) return infinity;
    Martian m1 = change2(value - 12, m0);
    Martian m2 = change2(value - 5, m0);
    Martian m3 = change2(value - 1, m0);
    return min(m0 + m1, m0 +  m2, m0 + m3);
}
