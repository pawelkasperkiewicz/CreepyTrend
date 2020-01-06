#include <RcppArmadillo.h>
#include <omp.h>
using namespace Rcpp;
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppArmadillo)]]

//Aggregation function
// [[Rcpp::export]]
arma::colvec Aggr(const arma::colvec& X, const arma::colvec& Y){

  int n = arma::max(X);
  arma::colvec y(n);

  arma::uvec I;
  arma::uvec F;
  //omp_set_num_threads(12);
  //#pragma omp parallel for shared(X, Y, y) private(I, F)
  for(int i=0; i<n; i++){
    I = i;
    F = arma::find(X == i+1);
    y.elem(I) = arma::mean(Y.rows(F));
  }

  return y;
}



arma::mat Fit_m(const arma::colvec & x, const arma::colvec & y, const arma::colvec& l, int cores) {

  int k; arma::colvec coef; arma::colvec fitted; arma::colvec constant(x.n_rows); arma::mat smoothed(x.n_rows, l.n_rows + 1); int n;

  constant.fill(1);
  arma::mat egzog(x.n_rows, 2);
  egzog.col(0) = x; egzog.col(1) = constant;

  smoothed.col(0) = x;
  n = y.n_rows;

// TODO set k variable to appropiate type and values. It should be vector or table with multiple valueb because of l is vactor now


  arma::uvec ids_f; arma::vec ids_t;

  arma::uvec IDs_f; arma::uvec IDs_t;

  arma::uvec j_v; arma::uvec i_v;
  //omp_set_num_threads(12);
  //#pragma omp parallel for shared(egzog, x, X, Y, k) private(ids, IDS)
  for (int j=0; j<n; j++){

    k = x.n_rows - l(j) + 1;
    arma::colvec Y(k*l.row(j));
    arma::colvec X(k*l.row(j));
    j_v = j;

    for (int i=0; i<k; i++){

      i_v = i;
      //ids = arma::linspace<arma::uvec>(i, i+l.elem(j_v)-1, l.elem(j_v));
      //IDs = arma::linspace<arma::uvec>(i*l.row(j), (l.row(j)*(i+1))-1, l.row(j));

      ids_f = i; ids_t = i+l.elem(j_v)-1;
      IDs_f = i+l.elem(j_v);


      coef = arma::solve(egzog.rows(ids), y.rows(ids));
      Y.elem(IDs) = egzog.rows(ids)*coef;
      X.elem(IDs) = x.rows(ids);
    }

    std::cout << "Before aggr\n";

    smoothed.col(j+1) = Aggr(X, Y);

}

  return smoothed;
}

