library(CreepyTrend)
library(ggplot2)

data <- data.table(
  x = seq.Date(as.Date("2000-01-01"), as.Date("2010-01-01"), "month"),
  y = sin(1:121)/3 + rnorm(121)/5 + (1:121)/100
)

R <- CreepyTrend$new(x = data$y)
R$fit(l = c(6, 10, 25))
R$smoothed

DT <- melt(R$smoothed, id.vars = "x")

ggplot(DT, aes(x, value, color = variable)) + geom_line()

