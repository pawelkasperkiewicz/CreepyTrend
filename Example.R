library(CreepyTrend)

#Create example time series with some seasonality and randomness
set.seed(666)
data <- data.table(
  x = seq.Date(as.Date("2000-01-01"), as.Date("2010-01-01"), "month"),
  y = sin(1:121)/3 + rnorm(121)/5 + (1:121)/100
)

R <- CreepyTrend$new(x = data$y)

R$fit(l = c(6, 10, 15, 25))

R$smoothed

R$plot()

R$plot(interactive = T)

R$plot() + ggtitle("Smoothed time series") + theme(plot.title = element_text(hjust = 0.5))



