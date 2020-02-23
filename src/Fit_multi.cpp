#include <RcppArmadillo.h>
using namespace Rcpp;
// [[Rcpp::depends(RcppArmadillo)]]

//' @export
//Aggregation function
// [[Rcpp::export]]
arma::colvec Aggr(const arma::colvec& X, const arma::colvec& Y){

  int n = arma::max(X);
  arma::colvec y(n);

  arma::uvec I;
  arma::uvec F;

  for(int i=0; i<n; i++){
    I = i;
    F = arma::find(X == i+1);
    y.elem(I) = arma::mean(Y.rows(F));
  }

  return y;
}

//' @export
// Fit function
// [[Rcpp::export]]
arma::mat Fit(const arma::colvec & x, const arma::colvec & y, arma::colvec& l, int cores) {
  int k; arma::colvec coef; arma::colvec fitted; arma::colvec constant(x.n_rows); arma::mat smoothed(x.n_rows, l.n_rows + 2); int n;

  constant.fill(1);
  arma::mat egzog(x.n_rows, 2);
  egzog.col(0) = x; egzog.col(1) = constant;

  smoothed.col(0) = x; smoothed.col(1) = y;
  n = l.n_rows;


  int ids_f; int ids_t;
  int IDs_f; int IDs_t;

  for (int j=0; j<n; j++){

    k = x.n_rows - arma::as_scalar(l.row(j)) + 1;
    arma::colvec Y((k*arma::as_scalar(l.row(j))));
    arma::colvec X(k*arma::as_scalar(l.row(j)));
    for (int i=0; i<k; i++){

      ids_f = i; ids_t = i+arma::as_scalar(l.row(j))-1;
      IDs_f = i*arma::as_scalar(l.row(j)); IDs_t = (arma::as_scalar(l.row(j))*(i+1))-1;

      coef = arma::solve(egzog.rows(ids_f, ids_t), y.rows(ids_f, ids_t));

      Y.rows(IDs_f, IDs_t) = egzog.rows(ids_f, ids_t)*coef;
      X.rows(IDs_f, IDs_t) = x.rows(ids_f, ids_t);
    }

    smoothed.col(j+2) = Aggr(X, Y);

}

  return smoothed;
}

