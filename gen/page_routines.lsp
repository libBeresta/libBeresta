(:файл "page_routines"
 :функции ((:название "Page_SetWidth"
            :группа "page"
            :ошибки ("INVALID_PAGE"
                     "PAGE_INVALID_SIZE"
                     "FAILED_TO_ALLOC_MEM")
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "REAL"
                         :имя "value"
                         :ru ""
                         :en "")))

           (:название "Page_SetHeight"
            :группа "page"
            :ошибки ("INVALID_PAGE"
                     "PAGE_INVALID_SIZE"
                     "FAILED_TO_ALLOC_MEM")
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "REAL"
                         :имя "value"
                         :ru ""
                         :en "")))

           (:название "Page_SetBoundary"
            :группа "page"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "PageBoundary"
                         :имя "boundary"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "left"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "bottom"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "right"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "top"
                         :ru ""
                         :en "")))

           (:название "Page_SetSize"
            :группа "page"
            :ошибки ("INVALID_PAGE"
                     "PAGE_INVALID_SIZE"
                     "PAGE_INVALID_ORIENTATION"
                     "FAILED_TO_ALLOC_MEM")
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "PageSizes"
                         :имя "size"
                         :ru ""
                         :en "")
                        (:тип "PageOrientation"
                         :имя "orientation"
                         :ru ""
                         :en "")))

           (:название "Page_SetRotate"
            :группа "page"
            :ошибки ("INVALID_PAGE"
                     "PAGE_INVALID_ROTATE_VALUE")
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "UINT16"
                         :имя "angle"
                         :ru ""
                         :en "")))

           (:название "Page_SetSlideShow"
            :группа "page"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "PageTransition"
                         :имя "type"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "disp_time"
                         :ru ""
                         :en "")
                        (:тип "REAL"
                         :имя "trans_time"
                         :ru ""
                         :en "")))

           (:название "Page_SetHorizontalScaling"
            :группа "graphics"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "REAL"
                         :имя "value"
                         :ru ""
                         :en "")))

           (:название "Page_GStateDepth"
            :группа "page"
            :ошибки ()
            :результат (:тип "UINT"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

           (:название "Page_HorizontalScaling"
            :группа "page"
            :ошибки ()
            :результат (:тип "REAL"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

           (:название "Page_SetZoom"
            :группа "page"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "REAL"
                         :имя "zoom"
                         :ru ""
                         :en "")))

           (:название "Page_Width"
            :группа "page"
            :ошибки ()
            :результат (:тип "REAL"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

           (:название "Page_Height"
            :группа "page"
            :ошибки ()
            :результат (:тип "REAL"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

           (:название "Page_GMode"
            :группа "page"
            :ошибки ()
            :результат (:тип "UINT16"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

;;           (:название "Page_CurrentPos"
;;            :группа "page"
;;            :ошибки ("INVALID_PAGE")
;;            :результат (:тип "Point"
;;                        :ru ""
;;                        :en "")
;;            :ru ""
;;            :en ""
;;            :команда ""
;;            :параметры ((:тип "Page"
;;                         :имя "page"
;;                         :ru ":param_page"
;;                         :en ":param_page")))

;;           (:название "Page_CurrentPos2"
;;            :группа "page"
;;            :ошибки ()
;;            :результат (:тип "STATUS"
;;                        :ru ""
;;                        :en "")
;;            :ru ""
;;            :en ""
;;            :команда ""
;;            :параметры ((:тип "Page"
;;                         :имя "page"
;;                         :ru ":param_page"
;;                         :en ":param_page")
;;                        (:тип "Point*"
;;                         :имя "pos"
;;                         :ru ""
;;                         :en "")))

           (:название "Page_MMgr"
            :группа "page"
            :ошибки ()
            :результат (:тип "MMgr"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))

;;           (:название "Page_New_Content_Stream"
;;            :группа "page"
;;            :ошибки ()
;;            :результат (:тип "STATUS"
;;                        :ru ""
;;                        :en "")
;;            :ru ""
;;            :en ""
;;            :команда ""
;;            :параметры ((:тип "Page"
;;                         :имя "page"
;;                         :ru ":param_page"
;;                         :en ":param_page")
;;                        (:тип "Dict*"
;;                         :имя "new_stream"
;;                         :ru ""
;;                         :en "")))

           (:название "Page_Insert_Shared_Content_Stream"
            :группа "page"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "Dict"
                         :имя "shared_stream"
                         :ru ""
                         :en "")))

           (:название "Page_RawWrite"
            :группа "page"
            :ошибки ("INVALID_PAGE")
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "CSTR"
                         :имя "data"
                         :ru ""
                         :en "")))

           (:название "Page_SetExtGState"
            :группа "graphics"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "ExtGState"
                         :имя "ext_gstate"
                         :ru ""
                         :en "")))

           (:название "Page_CreateDestination"
            :группа "link"
            :ошибки ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM")
            :результат (:тип "Destination"
                        :ru ""
                        :en "")
            :ru ""
            :en ""
            :команда ""
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")))))
