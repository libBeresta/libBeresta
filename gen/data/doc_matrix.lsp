(:file "doc_matrix"
 :functions ((:caption "Doc_Matrix_Identity"
	    :ru "Создается единичная матрица преобразований."
	    :en "Create identity transformation matrix."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf"))) 
	   (:caption "Doc_Matrix_Free"
	    :ru "Высвобождение памяти, занятой матрицей преобразований."
	    :en "Free transformation matrix memory."
	    :result (:type "void"
			:ru "Нет"
			:en "No")
	    :params ((:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix"))) 
	   
	   (:caption "Doc_Matrix_Multiply"
	    :ru "Перемножение матриц преобразований. Результирующая матрица - это перемножение матриц \\c m и \\c n."
	    :en "Multiply transformation matrices. Transformation matrix as a result of multiplication of matrices \\c m and \\c n."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "Matrix"
                         :name "n"
                         :ru ":param_matrix"
                         :en ":param_matrix"))) 

	   (:caption "Doc_Matrix_Translate"
	    :ru "Создание матрицы переноса на расстояние \\c dx и \\c dy."
	    :en "Create translate transformation matrix. Coordinates translated to \\c dx and \\c dy."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "REAL"
                         :name "dx"
                         :ru "Перенос координат по оси X."
                         :en "X axis translate value.")
			(:type "REAL"
                         :name "dy"
                         :ru "Перенос координат по оси Y."
                         :en "Y axis translate value.")))

	   (:caption "Doc_Matrix_Scale"
	    :ru "Создание матрицы масштабирования с коэффициентами \\c sx и \\c sy."
	    :en "Create scale transformation matrix. Coordinates scaled to \\c sx and \\c sy."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "REAL"
                         :name "sx"
                         :ru "Масштабный коэффициент по оси X."
                         :en "X axis scale value.")
			(:type "REAL"
                         :name "sy"
                         :ru "Масштабный коэффициент по оси Y."
                         :en "Y axis scale value.")))
	   (:caption "Doc_Matrix_Rotate"
	    :ru "Создание матрицы поворота на угол \\c angle (радиан)."
	    :en "Create rotate transformation matrix. Coordinates rotated to \\c angle (radians)."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params (
			(:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "REAL"
                         :name "angle"
                         :ru "Угол поворота координат (радиан)."
                         :en "Rotate angle value (radians).")))
	   (:caption "Doc_Matrix_RotateDeg"
	    :ru "Создание матрицы поворота на угол \\c angle (градусов)."
	    :en "Create rotate transformation matrix. Coordinates rotated to \\c angle (degrees)."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "REAL"
                         :name "degrees"
                         :ru "Угол поворота координат (градусов)."
                         :en "Rotate angle value (degrees).")))
	   (:caption "Doc_Matrix_Skew"
	    :ru "Создание матрицы сдвига на \\c a и \\c b по осям координат."
	    :en "Create skew transformation matrix. Coordinates skewed to \\c a and \\c b."
	    :result (:type "Matrix"
			:ru ":param_matrix"
			:en ":param_matrix")
	    :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf") 
			(:type "Matrix"
                         :name "m"
                         :ru ":param_matrix"
                         :en ":param_matrix")
			(:type "REAL"
                         :name "a"
                         :ru "Значение сдвига по оси X."
                         :en "X axis skew value.")
			(:type "REAL"
                         :name "b"
                         :ru "Значение сдвига по оси Y."
                         :en "Y axis skew value.")))))
