#ifndef SEARCHBOX_H
#define SEARCHBOX_H

//! [1]
#include <QLineEdit>

class GSuggestCompletion;

class SearchBox: public QLineEdit
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);

protected slots:
    void doSearch();

private:
    GSuggestCompletion *completer = nullptr;
//! [1]
};


#endif // SEARCHBOX_H
