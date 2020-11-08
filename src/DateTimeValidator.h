// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef DATETIMEVALIDATOR_H
#define DATETIMEVALIDATOR_H

#include <QValidator>

class DateTimeValidator : public QValidator {
    Q_OBJECT

 public:
    explicit DateTimeValidator();

    State validate(QString& input, int& pos) const;

};

#endif // DATETIMEVALIDATOR_H
