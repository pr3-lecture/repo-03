(defun neues-vorletztes (element list)
    (append
        (butlast list)
        (list element)
        (last list)
    )
)

(neues-vorletztes 4 `(1 2 3 5))
