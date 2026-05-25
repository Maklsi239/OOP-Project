#ifndef TERMINAL_THEME_H
#define TERMINAL_THEME_H

// ANSI colors for terminal UI (truecolor).

namespace term {
    constexpr const char reset[] = "\033[0m";
    constexpr const char bold[] = "\033[1m";
    constexpr const char dim[] = "\033[2m";

    constexpr const char title[] = "\033[1;38;2;203;166;247m";
    constexpr const char accent[] = "\033[38;2;137;220;235m";
    constexpr const char label[] = "\033[38;2;166;218;149m";
    constexpr const char ok[] = "\033[38;2;166;227;161m";
    constexpr const char err[] = "\033[38;2;243;139;168m";
    constexpr const char warn[] = "\033[38;2;249;226;175m";
    constexpr const char muted[] = "\033[38;2;108;112;134m";
    constexpr const char border[] = "\033[38;2;137;180;250m";
    constexpr const char prompt[] = "\033[38;2;205;214;244m";
    constexpr const char num[] = "\033[38;2;250;179;135m";
}

#endif
