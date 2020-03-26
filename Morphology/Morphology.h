#ifndef __MORPHOLOGY_H__
#define __MORPHOLOGY_H__

class Bitmap {
public:
  virtual unsigned sx() const = 0;
  virtual unsigned sy() const = 0;
  virtual unsigned sz() const = 0;

  virtual bool& operator()(unsigned x, unsigned y, unsigned z) = 0;
  virtual bool operator()(unsigned x, unsigned y, unsigned z) const = 0;

  virtual ~Bitmap(){}
};

class Transformation {
public:
  virtual void transform( Bitmap& ) = 0;
  virtual ~Transformation() {}
};

#endif
