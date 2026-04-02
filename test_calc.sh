#!/usr/bin/env bash
# =============================================================================
# test_calc.sh — тесты для консольной утилиты calculator
#
# Использование:
#   chmod +x test_calc.sh
#   ./test_calc.sh <путь_до_бинаря>
#
# Пример:
#   ./test_calc.sh ./calc
# =============================================================================

set -euo pipefail

CALC="${1:-./calc}"

# ---- цвета ------------------------------------------------------------------
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

# ---- счётчики ---------------------------------------------------------------
PASS=0
FAIL=0
SKIP=0

# =============================================================================
# Вспомогательные функции
# =============================================================================

# run_test <описание> <ожидаемый_exit_code> <ожидаемая_подстрока_в_stdout> [аргументы calc...]
run_test() {
    local desc="$1"
    local expected_exit="$2"
    local expected_output="$3"
    shift 3

    local actual_output
    local actual_exit

    # Важно: объявление local и присвоение разделены,
    # иначе "local" всегда возвращает 0 и маскирует exit-код команды.
    actual_output=$("$CALC" "$@" 2>&1) || actual_exit=$?
    actual_exit="${actual_exit:-0}"

    local ok=true

    if [[ "$actual_exit" != "$expected_exit" ]]; then
        ok=false
    fi

    if [[ -n "$expected_output" && "$actual_output" != *"$expected_output"* ]]; then
        ok=false
    fi

    if $ok; then
        echo -e "  ${GREEN}PASS${RESET}  $desc"
        (( PASS++ )) || true
    else
        echo -e "  ${RED}FAIL${RESET}  $desc"
        echo -e "         args    : $*"
        echo -e "         exit    : got=${actual_exit}  want=${expected_exit}"
        echo -e "         output  : ${actual_output}"
        if [[ -n "$expected_output" ]]; then
            echo -e "         want in : ${expected_output}"
        fi
        (( FAIL++ )) || true
    fi
}

section() {
    echo ""
    echo -e "${CYAN}══════════════════════════════════════════${RESET}"
    echo -e "${CYAN}  $1${RESET}"
    echo -e "${CYAN}══════════════════════════════════════════${RESET}"
}

# =============================================================================
# Проверка наличия бинаря
# =============================================================================

if [[ ! -x "$CALC" ]]; then
    echo -e "${YELLOW}WARN${RESET}: бинарь '$CALC' не найден или не исполняемый."
    echo      "       Тесты будут пропущены. Соберите утилиту и передайте путь:"
    echo      "       $0 <путь_до_бинаря>"
    exit 0
fi

# =============================================================================
# СЛОЖЕНИЕ (addition)
# =============================================================================
section "ADDITION"

run_test "2 + 3 = 5" \
    0 "result = 5" \
    --first 2 --second 3 --operation addition

run_test "-10 + 10 = 0" \
    0 "result = 0" \
    --first -10 --second 10 --operation addition

run_test "0 + 0 = 0" \
    0 "result = 0" \
    --first 0 --second 0 --operation addition

run_test "большие числа: 1000000 + 2000000 = 3000000" \
    0 "result = 3000000" \
    --first 1000000 --second 2000000 --operation addition

run_test "переполнение LONG_MAX + 1" \
    1 "overflow" \
    --first 9223372036854775807 --second 1 --operation addition

run_test "отсутствует --second → ошибка" \
    1 "second argument" \
    --first 5 --operation addition

# =============================================================================
# ВЫЧИТАНИЕ (subtraction)
# =============================================================================
section "SUBTRACTION"

run_test "10 - 3 = 7" \
    0 "result = 7" \
    --first 10 --second 3 --operation subtraction

run_test "0 - 0 = 0" \
    0 "result = 0" \
    --first 0 --second 0 --operation subtraction

run_test "-5 - (-3) = -2" \
    0 "result = -2" \
    --first -5 --second -3 --operation subtraction

run_test "переполнение LONG_MIN - 1" \
    1 "overflow" \
    --first -9223372036854775808 --second 1 --operation subtraction

run_test "отсутствует --second → ошибка" \
    1 "second argument" \
    --first 5 --operation subtraction

# =============================================================================
# УМНОЖЕНИЕ (multiplication)
# =============================================================================
section "MULTIPLICATION"

run_test "6 * 7 = 42" \
    0 "result = 42" \
    --first 6 --second 7 --operation multiplication

run_test "0 * 999 = 0" \
    0 "result = 0" \
    --first 0 --second 999 --operation multiplication

run_test "-3 * -4 = 12" \
    0 "result = 12" \
    --first -3 --second -4 --operation multiplication

run_test "-3 * 4 = -12" \
    0 "result = -12" \
    --first -3 --second 4 --operation multiplication

run_test "переполнение LONG_MAX * 2" \
    1 "overflow" \
    --first 9223372036854775807 --second 2 --operation multiplication

run_test "отсутствует --second → ошибка" \
    1 "second argument" \
    --first 5 --operation multiplication

# =============================================================================
# ДЕЛЕНИЕ (division)
# =============================================================================
section "DIVISION"

run_test "10 / 2 = 5" \
    0 "result = 5" \
    --first 10 --second 2 --operation division

run_test "7 / 3 = 2 (целочисленное)" \
    0 "result = 2" \
    --first 7 --second 3 --operation division

run_test "0 / 5 = 0" \
    0 "result = 0" \
    --first 0 --second 5 --operation division

run_test "-10 / 2 = -5" \
    0 "result = -5" \
    --first -10 --second 2 --operation division

run_test "деление на ноль → ошибка" \
    1 "Division on 0" \
    --first 10 --second 0 --operation division

run_test "переполнение LONG_MIN / -1" \
    1 "overflow" \
    --first -9223372036854775808 --second -1 --operation division

run_test "отсутствует --second → ошибка" \
    1 "second argument" \
    --first 5 --operation division

# =============================================================================
# ВОЗВЕДЕНИЕ В СТЕПЕНЬ (power)
# =============================================================================
section "POWER"

run_test "2 ^ 10 = 1024" \
    0 "result = 1024" \
    --first 2 --second 10 --operation power

run_test "5 ^ 1 = 5" \
    0 "result = 5" \
    --first 5 --second 1 --operation power

run_test "3 ^ 3 = 27" \
    0 "result = 27" \
    --first 3 --second 3 --operation power

run_test "-2 ^ 3 = -8" \
    0 "result = -8" \
    --first -2 --second 3 --operation power

run_test "отрицательный показатель → ошибка" \
    1 "not negative" \
    --first 2 --second -1 --operation power

run_test "2 ^ 0 = 1" \
    0 "result = 1" \
    --first 2 --second 0 --operation power

run_test "переполнение 2 ^ 63" \
    1 "overflow" \
    --first 2 --second 63 --operation power

run_test "отсутствует --second → ошибка" \
    1 "second argument" \
    --first 5 --operation power

# =============================================================================
# ФАКТОРИАЛ (factorial)
# =============================================================================
section "FACTORIAL"

run_test "0! = 1" \
    0 "result = 1" \
    --first 0 --operation factorial

run_test "1! = 1" \
    0 "result = 1" \
    --first 1 --operation factorial

run_test "5! = 120" \
    0 "result = 120" \
    --first 5 --operation factorial

run_test "10! = 3628800" \
    0 "result = 3628800" \
    --first 10 --operation factorial

run_test "20! = 2432902008176640000" \
    0 "result = 2432902008176640000" \
    --first 20 --operation factorial

run_test "отрицательный аргумент → ошибка" \
    1 "not negative" \
    --first -1 --operation factorial

run_test "переполнение 21!" \
    1 "overflow" \
    --first 21 --operation factorial

# =============================================================================
# НЕКОРРЕКТНЫЕ ВХОДНЫЕ ДАННЫЕ
# =============================================================================
section "INVALID INPUT"

run_test "нечисловое --first → ошибка" \
    1 "Invalid number for --first" \
    --first abc --second 2 --operation addition

run_test "нечисловое --second → ошибка" \
    1 "Invalid number for --second" \
    --first 5 --second xyz --operation addition

run_test "неизвестная операция → ошибка" \
    1 "Invalid value for --operation" \
    --first 5 --second 2 --operation modulo

run_test "отсутствует --first → usage" \
    1 "Usage" \
    --second 2 --operation addition

run_test "отсутствует --operation → usage" \
    1 "Usage" \
    --first 5 --second 2

run_test "нет аргументов → usage" \
    1 "Usage"

run_test "float вместо int → ошибка" \
    1 "Invalid number" \
    --first 3.14 --second 2 --operation addition

# =============================================================================
# ИТОГ
# =============================================================================
echo ""
echo -e "${CYAN}══════════════════════════════════════════${RESET}"
TOTAL=$(( PASS + FAIL ))
echo -e "  Итого: ${TOTAL}  |  ${GREEN}PASS: ${PASS}${RESET}  |  ${RED}FAIL: ${FAIL}${RESET}"
echo -e "${CYAN}══════════════════════════════════════════${RESET}"
echo ""

if [[ "$FAIL" -gt 0 ]]; then
    exit 1
fi
exit 0
