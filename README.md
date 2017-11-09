# Qt Software for Parabolic Mirror Surface Fit Regression

## Motivation

The [Cherenkov Telescope Array](https://www.cta-observatory.org/) is a prototype
telescope compromised of several independent mirror panels.
This software allows for the fitting of measured points on a given mirror panel based on a [regression algorithm]() in order to determine the accuracy of the panel as related
to the theoretical shape.

## Stack
The App is built on C++ using [Qt](https://www.qt.io/download-qt-for-application-development).
The algorithm logic uses the [Armadillo C++ Linear Algebra Library](http://arma.sourceforge.net/).
Plotting is done using [MathGL](http://mathgl.sourceforge.net/doc_en/Main.html).
[Boost C++ libraries](http://www.boost.org/) are also used.
