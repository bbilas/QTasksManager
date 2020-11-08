// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QDateTime>
#include "DateTimeValidator.h"

DateTimeValidator::DateTimeValidator() : QValidator() {

}

QValidator::State DateTimeValidator::validate(QString &input, int &pos) const {
    Q_UNUSED(pos);

    QDateTime dt = QDateTime::fromString(input, "dd/mm/yyyy hh:mm:ss");
    return dt.isValid() ? QValidator::Acceptable : QValidator::Invalid;
}
