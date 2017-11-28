(defun my-length (a)
	(cond 
		((null a) 0)
		((listp (car a))(+ (my-length (car a)) (my-length (cdr a))))
		(T (+ 1 (my-length (cdr a))))
	)
)

(my-length `(1 2 (3) 4 (5 6) 7 8 (9 (10 11) 12)))
