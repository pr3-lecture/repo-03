(defun my-reverse (remaining &optional reversed)
	(cond 
		((null remaining) reversed)
		(T (my-reverse (butlast remaining) (append reversed (last remaining))))	
	)
)

(my-reverse `(1 2 3 4))
(my-reverse `(1 2 (3 4) 5))