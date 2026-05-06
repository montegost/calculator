# calculator
Реализация консольного калькулятора

## build
```bash
cmake -B build
cmake --build build
sudo cmake --build build --target install
```

## usage
```bash
calculator --first <num> [--second <num>] --operation <addition|subtraction|multiplication|division|power|factorial.>
```

## tests
```bash
chmod +x test_calc.sh
./test_calc.sh <calc_path> 
```
