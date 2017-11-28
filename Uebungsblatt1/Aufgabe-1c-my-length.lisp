(defun my-length (list)
    (if (eql list `())
        0
        (+ 1 (my-length (cdr list)))
    )
)
(my-length `(a b c d e f g))
