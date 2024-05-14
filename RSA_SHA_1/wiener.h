#pragma once
#include <iostream>
#include <vector>
#include <cmath>

std::ostream& operator<<(std::ostream& os, std::vector<int> a) {
    for (int i = 0; i < a.size(); i++) {
        os << a[i];
        if (i != a.size() - 1) os << ", ";
    }
    return os;
}

std::vector<std::pair<int, int>> findConvergents(const std::vector<int>& continuedFraction) {
    std::vector<std::pair<int, int>> convergents;

    int h0 = 0, h1 = 1;
    int k0 = 1, k1 = 0;

    for (size_t i = 0; i < continuedFraction.size(); ++i) {
        int ai = continuedFraction[i];

        int hn = ai * h1 + h0;
        int kn = ai * k1 + k0;

        convergents.push_back(std::make_pair(hn, kn));

        h0 = h1;
        h1 = hn;
        k0 = k1;
        k1 = kn;
    }

    return convergents;
}

std::vector<int> numToContinious(int e, int N) {
    double num = (double)e / (double)N;
    double a = (int)num;
    double x = num - a;
    std::vector<int> res;
    res.emplace_back(a);
    for (int i = 0; i < 9; i++) {
        a = (int)(1 / x);
        x = (1 / x) - a;
        res.emplace_back(a);
    }
    return res;
}

void wiener() {
    int e = 17993;
    int N = 90581;

    //// d = 14
    //int e = 65537;
    //int N = 185323;

    auto f = numToContinious(e, N);
    std::cout << "Continuous e/N: {" << f << "}" << std::endl;

    auto convergents = findConvergents(f);
    std::cout << "Convergents:" << std::endl;
    for (size_t i = 0; i < convergents.size(); ++i) {
        std::cout << "k_" << i << " / d_" << i << ": " << convergents[i].first << " / " << convergents[i].second << std::endl;
    }
    std::cout << std::endl;

    for (size_t i = 0; i < convergents.size(); ++i) {
        if (convergents[i].first == 0) continue;
        double phi = (e * convergents[i].second - 1) / convergents[i].first;

        double D = pow(((N - phi) + 1), 2) - 4 * N;
        std::cout << "D = " << D << std::endl;

        double p = -((N - phi) + 1) + sqrt(D);
        p = p / 2;
        std::cout << "p = " << p << std::endl;

        double q = -((N - phi) + 1) - sqrt(D);
        q = q / 2;
        std::cout << "q = " << q << std::endl;

        if (N == q * p) {
            std::cout << "Wiener: N = pq (" << N << " = " << p << " * " << q << ")" << std::endl;
            std::cout << "d = " << convergents[i].second << std::endl;
            std::cout << "d < [N^(1/4)] / 3 ~= " << sqrt(sqrt(static_cast<float> (N))) / 3 << std::endl;
            break;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

