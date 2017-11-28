(setq baum '( 5 ( 2 (1 nil nil) (3 nil (4 nil nil) )) (6 nil nil)))

;Inorder: 1, 2, 3, 4, 5, 6

(defun inorder(baum) ;print all elements inorder
    (if
        (not (null (second baum))) 
        (inorder (second baum)) ;print second elemnt when it is not null
     )
    (print (first baum))
    (if
         (not (null (third baum)))
         (inorder (third baum))
     )
)

(inorder baum)
