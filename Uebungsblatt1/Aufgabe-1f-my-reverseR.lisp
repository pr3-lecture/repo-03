(defun my-reverseR (remaining &optional reversed)
	(print remaining)
	(print reversed)
	(cond
		((null remaining) (print "null") reversed)
		((listp (car (last remaining))) (print "listp")
			(my-reverseR 
				(butlast remaining) 
				(append reversed 
					(list (my-reverseR (car (last remaining))))
				)
			)
		)
		(T (print "T") (my-reverseR (butlast remaining) (append reversed (last remaining))))
	)
)

(my-reverseR `(1 2 3 4))
(my-reverseR `(1 2 (3 4) 5))
(my-reverseR `(1 2 (3 4) 5 (6 (7 8) 9) 10))