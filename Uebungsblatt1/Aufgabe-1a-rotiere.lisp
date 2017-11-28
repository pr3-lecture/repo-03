(defun rotiere (list)
    (append
        (cdr list)
        (list (car list))
    )
)

(rotiere `(1 2 3 4))
