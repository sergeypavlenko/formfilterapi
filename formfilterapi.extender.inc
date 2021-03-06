<?php

/**
 * @file
 * Filter query extender and helper functions.
 */

/**
 * Query extender for form query condition.
 */
class FormFilterAPI extends SelectQueryExtender {
  /**
   * The filter name.
   *
   * @var string
   */
  protected $filterName;

  /**
   * Sets up the filter name.
   *
   * @param string $filter_name
   *   A filter name.
   *
   * @return object
   *   The SearchQuery object.
   */
  public function processFilters($filter_name) {
    $this->filterName = $filter_name;

    $filters = formfilterapi_build_filter_query($this->filterName);

    if (is_array($filters['where'])) {
      foreach ($filters['where'] as $cond) {
        foreach ($cond as $field => $value) {
          if (is_array($value)) {
            switch ($value['op']) {
              case 'like':
                $this->condition($field, "%" . $value['value'] . "%", 'LIKE');
                break;

              case 'operation':
                list($operation,$opval) = explode(' ', $value['value']);
                $this->condition($field, $opval, $operation);
                break;
            }
          }
          else {
            $this->condition($field, $value);
          }
        }
      }
    }

    return $this;
  }
}
