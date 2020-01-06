library(CreepyTrend)
library(microbenchmark)
library(ggplot2)
x <- rep(c(1:30000), length.out = 1000000)
y <- rnorm(1000000)

dt <- data.table(x, y)


res <- microbenchmark(list = list(
  D.T = {DT <- dt[, .(Mean = mean(y)), x]},
  Cpp = {CPP <- Agg(x, y)}
), times = 20)

autoplot(res)
