(:файл "doc_matrix"
 :функции ((:название "Doc_Matrix_Identity"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf"))) 
	   (:название "Doc_Matrix_Free"
	    :ru ""
	    :en ""
	    :результат (:тип "void"
			:ru ""
			:en "")
	    :параметры ((:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix"))) 
	   
	   (:название "Doc_Matrix_Multiply"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "Matrix"
                         :имя "n"
                         :ru ":param_matrix"
                         :en ":param_matrix"))) 

	   (:название "Doc_Matrix_Translate"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "REAL"
                         :имя "dx"
                         :ru ""
                         :en "")
			(:тип "REAL"
                         :имя "dy"
                         :ru ""
                         :en ""))) 

	   (:название "Doc_Matrix_Scale"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "REAL"
                         :имя "sx"
                         :ru ""
                         :en "")
			(:тип "REAL"
                         :имя "sy"
                         :ru ""
                         :en ""))) 
	   (:название "Doc_Matrix_Rotate"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры (
			(:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "REAL"
                         :имя "angle"
                         :ru ""
                         :en ""))) 
	   (:название "Doc_Matrix_RotateDeg"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "REAL"
                         :имя "degrees"
                         :ru ""
                         :en ""))) 
	   (:название "Doc_Matrix_Skew"
	    :ru ""
	    :en ""
	    :результат (:тип "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:тип "Matrix"
                         :имя "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:тип "REAL"
                         :имя "a"
                         :ru ""
                         :en "")
			(:тип "REAL"
                         :имя "b"
                         :ru ""
                         :en "")))))
