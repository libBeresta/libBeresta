(:файл "encrypt"
 :перечисления
       ((:имя "EncryptMode"
	 :ru "Режим шифрования документа (7.6 Encryption)"
	 :en "Document encryption mode (7.6 Encryption)"
	 :элементы (
		    ;; TODO Добавить проверку на это значение
		    (:элемент "ENCRYPT_R0"
		     :значение "0"
		     :en "An algorithm that is undocumented. This value shall not be used."
		     :ru "Недокументированный алгоритм. Значение не должно использоваться.")
		    (:элемент "ENCRYPT_R1"
		     :значение "1"
		     :en "Algorithm 1: Encryption of data using the RC4 or AES algorithms. \"General Encryption Algorithm\" with an encryption key length of 40 bits."
		     :ru "Алгоритм 1: Шифрование данных с использование алгоритмов RC4 и AES. \"Обобщенный алгоритм шифрования\" с ключами шифрования длиной 40 бит.")
		    (:элемент "ENCRYPT_R2"
		     :значение "2"
		     :en "Algorithm 1: Encryption of data using the RC4 or AES algorithms. \"General Encryption Algorithm\" but permitting encryption key lengths greater than 40 bits."
		     :ru "Алгоритм 1: Шифрование данных с использование алгоритмов RC4 и AES. \"Обобщенный алгоритм шифрования\" с ключами шифрования длиной более 40 бит."
		     :версия "1.4")
		    (:элемент "ENCRYPT_R3"
		     :значение "3"
		     :en "An unpublished algorithm that permits encryption key lengths ranging from 40 to 128 bits."
		     :ru "Неопубликованный алгоритм, позволяющий шифрование с ключами от 40 до 128 бит."
		     :версия "1.4")
		    (:элемент "ENCRYPT_R4"
		     :значение "4"
		     :en "The security handler defines the use of encryption and decryption in the document."
		     :ru "Управление шифрованием документа определяется настройками безопасности в документе."
		     :версия "1.5"))))))
