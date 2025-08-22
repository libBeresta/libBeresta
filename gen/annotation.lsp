(:файл "annotation"
 :импорты ("types" "dict" "destination")
 :определения
       ((:имя "Annotation"
	 :оригинал "Dict"))
 :перечисления
       ((:имя "AnnotType"
	 :ru "Тип аннотации (12.5.6 Annotation Types)"
	 :en "Annotation type (12.5.6 Annotation Types)"
	 :элементы ((:элемент "ANNOT_TEXT"                          :en "Text annotation"               :ru "Текстовая пометка")
		    (:элемент "ANNOT_LINK"                          :en "Link annotation"               :ru "Пометка ссылкой")
		    (:элемент "ANNOT_FREE_TEXT"       :версия "1.3" :en "Free text annotation"          :ru "Пометка свободным текстом")
		    (:элемент "ANNOT_LINE"            :версия "1.3" :en "Line annotation"               :ru "Пометка линией")
		    (:элемент "ANNOT_SQUARE"          :версия "1.3" :en "Square annotation"             :ru "Пометка квадратом")
		    (:элемент "ANNOT_CIRCLE"          :версия "1.3" :en "Circle annotation"             :ru "Пометка окружностью")
		    (:элемент "ANNOT_POLYGON"         :версия "1.5" :en "Polygon annotation"            :ru "Пометка полигоном")
		    (:элемент "ANNOT_POLYLINE"        :версия "1.5" :en "Polyline annotation"           :ru "Пометка ломаной линией")
		    (:элемент "ANNOT_HIGHLIGHT"       :версия "1.3" :en "Highlight annotation"          :ru "Пометка выделением")
		    (:элемент "ANNOT_UNDERLINE"       :версия "1.3" :en "Underline annotation"          :ru "Пометка подчеркиванием")
		    (:элемент "ANNOT_SQUIGGLY"        :версия "1.4" :en "Squiggly-underline annotation" :ru "Пометка волнистой линией")
		    (:элемент "ANNOT_STRIKEOUT"       :версия "1.3" :en "Strikeout annotation"          :ru "Пометка перечеркиванием")
		    (:элемент "ANNOT_STAMP"           :версия "1.3" :en "Rubber stamp annotation"       :ru "Пометка штампом")
		    (:элемент "ANNOT_CARET"           :версия "1.5" :en "Caret annotation"              :ru "Пометка символом абзаца")
		    (:элемент "ANNOT_INK"             :версия "1.3" :en "Ink annotation"                :ru "Пометка кистью")
		    (:элемент "ANNOT_POPUP"           :версия "1.3" :en "Pop-up annotation"             :ru "Пометка всплывающей подсказкой")
		    (:элемент "ANNOT_FILE_ATTACHMENT" :версия "1.3" :en "File attachment annotation"    :ru "Пометка файловым вложением")
		    (:элемент "ANNOT_SOUND"           :версия "1.2" :en "Sound annotation"              :ru "Пометка звуком")
		    (:элемент "ANNOT_MOVIE"           :версия "1.2" :en "Movie annotation"              :ru "Пометка видео")
		    (:элемент "ANNOT_WIDGET"          :версия "1.2" :en "Widget annotation"             :ru "Пометка виджетом")
		    (:элемент "ANNOT_SCREEN"          :версия "1.5" :en "Screen annotation"             :ru "Пометка на экране")
		    (:элемент "ANNOT_PRINTER_MARK"    :версия "1.4" :en "Printer’s mark annotation"     :ru "Пометка знаком принтера")
		    (:элемент "ANNOT_TRAPNET"         :версия "1.3" :en "Trap network annotation"       :ru "Пометка цветового перекрытия")
		    (:элемент "ANNOT_WATERMARK"       :версия "1.6" :en "Watermark annotation"          :ru "Пометка водным знаком")
		    (:элемент "ANNOT_3D"              :версия "1.6" :en "3D annotation"                 :ru "3D пометка")
		    (:элемент "ANNOT_REDACT"          :версия "1.7" :en "Redact annotation"             :ru "Редакторская пометка")))

	(:имя "AnnotFlags"
	 :ru "Флаги аннотации (12.5.3 Annotation Flags)"
	 :en "Annotation flags (12.5.3 Annotation Flags)"
	 :версия "1.1"
	 :элементы ((:элемент  "ANNOT_FLAG_INVISIBLE")
		    (:элемент  "ANNOT_FLAG_HIDDEN"         :версия "1.2")
		    (:элемент  "ANNOT_FLAG_PRINT"          :версия "1.2")
		    (:элемент  "ANNOT_FLAG_NOZOOM"         :версия "1.3")
		    (:элемент  "ANNOT_FLAG_NOROTATE"       :версия "1.3")
		    (:элемент  "ANNOT_FLAG_NOVIEW"         :версия "1.3")
		    (:элемент  "ANNOT_FLAG_READONLY"       :версия "1.3")
		    (:элемент  "ANNOT_FLAG_LOCKED"         :версия "1.4")
		    (:элемент  "ANNOT_FLAG_TOGGLE_NOVIEW"  :версия "1.5")
		    (:элемент  "ANNOT_FLAG_LOCKED_CONTENT" :версия "1.7")))

	(:имя "AnnotHighlightMode"
	 :версия "1.2"
	 :ru "Режим выделения пометки, визуальный эффект, используемый при нажатии или удержании кнопки мыши внутри активного региона (12.5.6.5 Link Annotations)"
	 :en "The annotation’s highlighting mode, the visual effect that shall be used when the mouse button is pressed or held down inside its active area (12.5.6.5 Link Annotations)"
	 :элементы ((:элемент "ANNOT_HIGHLIGHT_MODE_NONE"
		     :ru "Без выделения"
		     :en "No highlight")

		    (:элемент "ANNOT_HIGHLIGHT_MODE_INVERT"
		     :ru "Инверсия содержимого прямоугольника пометки."
		     :en "Invert the contents of the annotation rectangle.")

		    (:элемент "ANNOT_HIGHLIGHT_MODE_OUTLINE"
		     :ru "Инверсия рамки пометки."
		     :en "Invert the annotation’s border.")

		    (:элемент "ANNOT_HIGHLIGHT_MODE_PUSH"
		     :ru "Демонстрация пометки, как если бы она была утоплена ниже поверхности страницы."
		     :en "Display the annotation as if it were being pushed below the surface of the page.")))

	(:имя "AnnotIcon"
	 :en "Default types of annotation icon (12.5.6.4 Text Annotations)."
	 :ru "Типы иконок пометок (12.5.6.4 Text Annotations)."
	 :элементы ((:элемент "ANNOT_ICON_COMMENT"       :ru "Комментарий" :en "Comment")
		    (:элемент "ANNOT_ICON_KEY"           :ru "Ключ"        :en "Key")
		    (:элемент "ANNOT_ICON_NOTE"          :ru "Заметка"     :en "Note")
		    (:элемент "ANNOT_ICON_HELP"          :ru "Помощь"      :en "Help")
		    (:элемент "ANNOT_ICON_NEW_PARAGRAPH" :ru "Новый абзац" :en "New paragraph")
		    (:элемент "ANNOT_ICON_PARAGRAPH"     :ru "Абзац"       :en "Paragraph")
		    (:элемент "ANNOT_ICON_INSERT"        :ru "Вставка"     :en "Insert")))

	(:имя "AnnotLineEnd"
	 :en "Types of annotation lines (12.5.6.7 Line Annotations)."
	 :ru "Типы концовок линий пометок (12.5.6.7 Line Annotations)."
	 :версия "1.3"
	 :элементы ((:элемент "ANNOT_LINE_END_NONE"
                     :ru "Нет концовки"
		     :en "No line ending")
		    (:элемент "ANNOT_LINE_END_SQUARE"
                     :ru "Квадрат, заполненный цветом наполнения пометки, если он задан"
		     :en "A square filled with the annotation’s interior color, if any")
		    (:элемент "ANNOT_LINE_END_CIRCLE"
                     :ru "Окружность, заполненная цветом наполнения пометки, если он задан"
		     :en "A circle filled with the annotation’s interior color, if any")
		    (:элемент "ANNOT_LINE_END_DIAMOND"
		     :ru "Ромб, заполненный цветом наполнения пометки, если он задан"
		     :en "A diamond shape filled with the annotation’s interior color, if any")
		    (:элемент "ANNOT_LINE_END_OPENARROW"
                     :ru "Две короткие линии, пересекающиеся под острым углом в форме открытой стрелочки"
		     :en "Two short lines meeting in an acute angle to form an open arrowhead")
		    (:элемент "ANNOT_LINE_END_CLOSEDARROW"
		     :ru "Две короткие линии, пересекающиеся под острым углом, как в OpenArrow, соединенные третьей линией и образующие закрытую треугольную стрелочку, заполненную цветом наполнения пометки, если он задан."
		     :en "Two short lines meeting in an acute angle as in the OpenArrow style and connected by a third line to form a triangular closed arrowhead filled with the annotation’s interior color, if any")
		    (:элемент "ANNOT_LINE_END_BUTT"
		     :версия "1.5"
		     :ru "Короткий отрезок на конце, перпендикулярный к линии"
		     :en "A short line at the endpoint perpendicular to the line itself")
		    (:элемент "ANNOT_LINE_END_ROPENARROW"
		     :версия "1.5"
		     :ru "Две короткие линии в направлении, обратном к OpenArrow"
		     :en "Two short lines in the reverse direction from OpenArrow")
		    (:элемент "ANNOT_LINE_END_RCLOSEDARROW"
		     :версия "1.5"
		     :ru "Треугольная стрелочка, в направлении, обратном к ClosedArrow"
		     :en "A triangular closed arrowhead in the reverse direction from ClosedArrow")
		    (:элемент "ANNOT_LINE_END_SLASH"
		     :версия "1.6"
		     :ru "Короткий отрезок на конце линии, наклоненный примерно на 30 градусов по часовой стрелке от перпендикуляра к линии."
		     :en "A short line at the endpoint approximately 30 degrees clockwise from perpendicular to the line itself")))

	(:имя "AnnotLineCapPosition"
	 :en "Types of line annotation cap position (12.5.6.7 Line Annotations, table 175)."
	 :ru "Типы расположений заголовка линий пометок (12.5.6.7 Line Annotations, таблица 175)."
	 :версия "1.7"
	 :элементы ((:элемент "ANNOT_LINE_CAP_INLINE"
		     :ru "Заголовок будет центрирован внутри линии"
		     :en "Caption shall be centered inside the line")
		    (:элемент "ANNOT_LINE_CAP_TOP"
		     :ru "Заголовок будет расположен над линией"
		     :en "Caption shall be on top of the line")))

	(:имя "AnnotStampStyle"
	 :en "Predefined rubber stamp styles (12.5.6.12 Rubber Stamp Annotations, tab. 181)."
	 :ru "Предопределенные стили пометок штампом (12.5.6.12 Rubber Stamp Annotations, tab. 181)."
	 :версия "1.3"
	 :элементы ((:элемент "ANNOT_STAMP_APPROVED"             :ru "Согласовано" :en "Approved")
		    (:элемент "ANNOT_STAMP_EXPERIMENTAL"         :ru "Экспериментально" :en "Experimental")
		    (:элемент "ANNOT_STAMP_NOTAPPROVED"          :ru "Не согласовано" :en "Not Approved")
		    (:элемент "ANNOT_STAMP_ASIS"                 :ru "Как есть" :en "As Is")
		    (:элемент "ANNOT_STAMP_EXPIRED"              :ru "Просрочено" :en "Expired")
		    (:элемент "ANNOT_STAMP_NOTFORPUBLICRELEASE"  :ru "Не для публичной демонстрации" :en "Not For Public Release")
		    (:элемент "ANNOT_STAMP_CONFIDENTIAL"         :ru "Конфиденциально" :en "Confidential")
		    (:элемент "ANNOT_STAMP_FINAL"                :ru "Финальная версия" :en "Final")
		    (:элемент "ANNOT_STAMP_SOLD"                 :ru "Продано" :en "Sold")
		    (:элемент "ANNOT_STAMP_DEPARTMENTAL"         :ru "Ведомственное" :en "Departmental")
		    (:элемент "ANNOT_STAMP_FORCOMMENT"           :ru "Для заметок" :en "For Comment")
		    (:элемент "ANNOT_STAMP_TOPSECRET"            :ru "Секретно" :en "Top Secret")
		    (:элемент "ANNOT_STAMP_DRAFT"                :ru "Черновик" :en "Draft")
		    (:элемент "ANNOT_STAMP_FORPUBLICRELEASE"     :ru "Для публичной демонстрации" :en "For Public Release")))

	))

