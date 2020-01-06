# CreepyTrend

Fast implementation of method based on moving trend algorithm using C++ and RcppArmadillo.
Actually in intensive developing.
<br><br>
## Simple usage for smoothing time series
Instalation
``` r
remotes::install_github("pawelkasperkiewicz/CreepyTrend", type = "source")
```
<br>
``` r
library(ggplot2)
library(CreepyTrend)
data <- data.table(
  x = seq.Date(as.Date("2000-01-01"), as.Date("2010-01-01"), "month"),
  y = sin(1:121)/3 + rnorm(121)/5 + (1:121)/100
  )

Model <- CreepyTrend$new(data$y)
Model$fit(l = 6)
ggplot(data, aes(x, y)) + geom_line() + geom_line(aes(y = Model$smoothed$y, color = "red"))
```
<br>
![](Smoothed.jpeg)
