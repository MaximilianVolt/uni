<?php



declare(strict_types=1);



namespace W01;



class Validator
{
	public const array FILTERS = [
    ValidatorFilter::VALIDATE_STRING->value => FILTER_SANITIZE_FULL_SPECIAL_CHARS,
    ValidatorFilter::VALIDATE_STRING_ARR->value => [
			'filter' => FILTER_SANITIZE_FULL_SPECIAL_CHARS,
			'flags' => FILTER_REQUIRE_ARRAY
    ],
    ValidatorFilter::VALIDATE_EMAIL->value => FILTER_VALIDATE_EMAIL,
    ValidatorFilter::VALIDATE_INT->value => [
			'filter' => FILTER_VALIDATE_INT,
			'flags' => FILTER_REQUIRE_SCALAR
    ],
    ValidatorFilter::VALIDATE_INT_ARR->value => [
			'filter' => FILTER_VALIDATE_INT,
			'flags' => FILTER_REQUIRE_ARRAY
    ],
    ValidatorFilter::VALIDATE_FLOAT->value => [
			'filter' => FILTER_VALIDATE_FLOAT,
			'flags' => FILTER_FLAG_ALLOW_FRACTION
    ],
    ValidatorFilter::VALIDATE_FLOAT_ARR->value => [
			'filter' => FILTER_VALIDATE_FLOAT,
			'flags' => FILTER_REQUIRE_ARRAY
    ],
    ValidatorFilter::VALIDATE_URL->value => FILTER_VALIDATE_URL,
	];



  /**
	* Sanitize the inputs based on the rules an optionally trim the string
	* @param array $inputs
	* @param array $fields
	* @param int $default_filter FILTER_SANITIZE_FULL_SPECIAL_CHARS
	* @param array $filters FILTERS
	* @param bool $trim
	* @return array
	*/

	public static function validate(array $inputs, array $fields = [], int $default_filter = FILTER_SANITIZE_FULL_SPECIAL_CHARS, array $filters = Validator::FILTERS, bool $trim = false): array
	{
		$options = $default_filter;

		if ($fields)
			$options = array_map(fn($field) => $filters[$field->value], $fields);

		$data = filter_var_array($inputs, $options);

		return $trim
			? static::arrayTrim($data)
			: $data
		;
	}



	/**
	* Recursively trim strings in an array
	* @param array $items
	* @return array
	*/
	public static function arrayTrim(array $items): array
	{
		return array_map(fn($item) => is_string($item)
			? trim($item)
			: (
				is_array($item)
					? static::arrayTrim($item)
					: $item
			),
			$items
		);
	}
}
