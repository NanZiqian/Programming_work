# 8-1 Personal Diary

南子谦 3210104676 信息与计算科学

注意：所有日期必须是XXXX.XX.XX的格式，如2023.4.27！否则会出严重错误。

## 如何使用日记程序

在console中，您将可以输入以下函数

- pdadd (2023.08.06)

  - --> add an entity of a date, the existing one will be replaced. Read the dairy line by line until a line with a single "." or EOF.
  - //if not given the date, apply present time.
- pdlist (2023.08.06 2023.08.26)

  - --> lists all [increasingly ordered] by date, if start and end provided, list between.
  - //if not given time, request to input time.
- pdshow (2023.08.06)

  - --> prints the content with the date.
- pdremove (2023.08.06)

  - --> remove a diary of the date, and inform user whether deleted properly.
- help
- exit

  - -->exit the program

例如

```
help
pdlsit
pdshow 2023.4.25
pdlsit 2022.08.06 2023.08.26
```

so on and so forth.
