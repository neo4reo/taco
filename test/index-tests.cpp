#include "test.h"
#include "test_tensors.h"

#include "taco/format.h"
#include "taco/storage/index.h"
#include "taco/storage/array.h"

using namespace taco;
using namespace taco::storage;

TEST(index, size) {
  Index index = makeCSRIndex({0, 1, 3, 4, 6}, {0, 0, 3, 1, 1, 2});
  ASSERT_EQ(6u, index.getSize());

  index = Index(Format({Dense,Dense}),
                {DimensionIndex({Array({3})}), DimensionIndex({Array({4})})});
  ASSERT_EQ(12u, index.getSize());
}

TEST(index, makeCSR) {
  vector<int> rowptr = {0, 1, 3, 4, 6};
  vector<int> colidx = {0, 0, 3, 1, 1, 2};

  Index index = makeCSRIndex(rowptr, colidx);
  ASSERT_EQ(2u, index.numDimensionIndices());
  ASSERT_EQ(1u, index.getDimensionIndex(0).numIndexArrays());
  ASSERT_EQ(2u, index.getDimensionIndex(1).numIndexArrays());

  auto rowptrarray = index.getDimensionIndex(1).getIndexArray(0);
  ASSERT_ARRAY_EQ(rowptr, {rowptrarray.getData(), rowptrarray.getSize()});

  auto colidxarray = index.getDimensionIndex(1).getIndexArray(1);
  ASSERT_ARRAY_EQ(colidx, {colidxarray.getData(), colidxarray.getSize()});
}